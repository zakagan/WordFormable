import sys, os, re
import matplotlib.pyplot as plt

def averageList(l):
	return sum(l)/ len(l)

def parseTime(time_str):
# reads time stamps in the format [x]m[y]s, and consverts them to (x*60)+y seconds
	time_list=re.split("[ms]", time_str)
	try:
		minutes=float(time_list[0])
		seconds=float(time_list[1])
		return (minutes*60)+seconds
	except:
		print("Time values were not properly parsed:", sys.exc_info()[0])
		raise

class record(object):
# Basic data object that contains x value and a collection of y values to be averaged
	def __init__(self, x_val, y_val_list):
		self.x_val=x_val
		self.y_val_list=y_val_list
		self.average_y=False

	def yAppend(self, new_y_list):
		self.y_val_list.append(new_y_list)

	def ProcessAverage(self):
		self.average_y=averageList(self.y_val_list)

class dataset(object):
# object containing a collection of records that correspond to one solution, and more generally one particular tests sequence

	def __init__(self, solution, record_list):
		self.solution=solution
		self.data=record_list

	def addRecords(self, new_record_list):
		ridx=0     #running index of older records
		for new_record in new_record_list:
			while ridx <= len(self.data)-1:
				if new_record.x_val > self.data[ridx].x_val and ridx!=len(self.data)-1:
					ridx+=1
					continue
				elif new_record.x_val == self.data[ridx].x_val:
					# combines y vals for a single x val together into the same record
					self.data[ridx].yAppend(new_record.y_val_list)
					ridx+=1
					break
				elif new_record.x_val < self.data[ridx].x_val:
					self.data.insert(ridx,new_record)
					ridx+=1
					break
				else:
					# must be at end of list
					self.data.insert(ridx+1,new_record)
					ridx+=1
					break

	def postProcess(self, func):
		for record in self.data:
			if func:
				record.x_val=func(record.x_val)
			record.ProcessAverage()

	def getXValues(self):
		return [d.x_val for d in self.data]

	def getYValues(self):
		return[d.average_y for d in self.data if d.average_y]

class grapher(object):
#object the finds data from test files, processes them into the previous objects, and sets them up to be graphed via matplotlib

	def __init__(self, dirname_regex, x_var_pattern):
		self.x_var_pattern=x_var_pattern
		self.first_base_string_length=None
		self.first_num_chars=None
		self.first_num_tokens=None
		self.first_num_formable=None
		self.graph_title=None
		self.datasets=[]
		#gnarley list comprehension that gathers a list of dirs from current directory that match a regex
		test_results=[m.group(0) for l in [d for d in os.listdir() if os.path.isdir(d)] for m in [re.search(dirname_regex,l)] if m]
		result_dir=os.path.realpath(test_results[-1])
		os.chdir(result_dir)
		#Here the test results files are selected
		for idx,file_path in enumerate([f for f in os.listdir() if f.endswith(".txt")]):
			if idx==0:
				f = open(file_path,'r')
				for jdx,line in enumerate(f):
					text_list=line.split()
					if self.first_num_chars and self.first_num_tokens and self.first_num_formable and self.graph_title:
						break
					elif jdx == 0 and self.graph_title is None:
						self.graph_title=line
					elif self.first_base_string_length is None and "Base string length:" in line:
						self.first_base_string_length=int(text_list[text_list.index('length:')+1])
					elif self.first_num_chars is None and "Number of chars read from file:" in line:
						self.first_num_chars=int(text_list[text_list.index('file:')+1])
					elif self.first_num_tokens is None and "Number of tokenized words read from file:" in line:
						self.first_num_tokens=int(text_list[text_list.index('file:')+1])
					elif self.first_num_formable is None and "Number of words formable from the base string:" in line:
						self.first_num_formable=int(text_list[text_list.index('string:')+1])
				f.close()
			self.datasets.append(self._readData(file_path))
		#check for and combine any duplicate solution datasets
		temp_dataset_list=[]
		for current_dataset in self.datasets:
			for moved_dataset in temp_dataset_list:
				if current_dataset.solution == moved_dataset.solution:
					moved_dataset.addRecords(current_dataset.data)
					break
			else:
				temp_dataset_list.append(current_dataset)
		self.datasets=temp_dataset_list

		os.chdir(os.path.dirname(result_dir))

	def _readData(self, file_path):
	#method that actually grabs x and y data from file and processes them into record objects
			data_list=[]
			solution=None
			x=None
			y=None
			y_vals=[]
			f = open(file_path,'r')
			#Here the files are read and parsed
			for line in f:
				text_list=line.split()
				if not solution and 'SOLUTION:' in line:
					solution=text_list[text_list.index('SOLUTION:')+1]
				elif self.x_var_pattern in line:
					if x is not None and y_vals and None not in y_vals:
						r=record(x,y_vals)
						data_list.append(r)
						x=None
						y_vals=[]
					x=int(text_list[text_list.index(self.x_var_pattern)+1])
				elif "user" in line:
					y=parseTime(text_list[1])
				elif "sys" in line:
					y+=parseTime(text_list[1])
					y_vals.append(y)
					y=None
				else:
					pass
			else:
				if x is not None and y_vals and None not in y_vals:
					r=record(x,y_vals)
					data_list.append(r)
					x=None
					y_vals=[]
			f.close()
			d=dataset(solution,data_list)
			return d

	def combineData(self, dirname_regex):
	#method to add data from another folder of test files to the current collection of datasets
		test_results=[m.group(0) for l in [d for d in os.listdir() if os.path.isdir(d)] for m in [re.search(dirname_regex,l)] if m]
		result_dir=os.path.realpath(test_results[-1])
		os.chdir(result_dir)
		#Here the test results files are selected
		for file_path in [f for f in os.listdir() if f.endswith(".txt")]:
			d=self._readData(file_path)
			success=0
			for current_d in self.datasets:
				if d.solution == current_d.solution:
					success=1
					current_d.addRecords(d.data)
					break
		if not success:
			print("Datasets with different solution names cannot be combined.")
		os.chdir(os.path.dirname(result_dir))

	def chart(self):
	#actually prepares charts. Should not be called by non-sub classes as more definitions are needed
		fig=plt.figure()
		ax1=fig.add_subplot(111)
		for idx,d in enumerate(self.datasets):
			ax1.plot(d.getXValues(), d.getYValues(), self.point_style_list[idx], label=d.solution)
		plt.xlim(self.x_lower_bound,self.x_upper_bound)
		plt.ylim(self.y_lower_bound,self.y_upper_bound)
		plt.xlabel(self.xlabel)
		plt.ylabel(self.ylabel)
		#plt.xscale('log')
		plt.legend(loc='upper left')
		plt.show()

class grapherNW(grapher):

	def __init__(self):
		grapher.__init__(self, "num_words_\d+", "XWORDS:")
		for d in self.datasets:
			d.postProcess(lambda x: self.first_num_tokens * x)

		self.point_style_list=['rs-', 'bs-', 'gs-', 'ms-']
		self.xlabel="Number of words in text file"
		self.ylabel="Computation Time (Sec)"
		self.x_lower_bound=0
		self.x_upper_bound=max([d.data[-1].x_val for d in self.datasets])
		self.y_lower_bound=0
		self.y_upper_bound=max([d.data[-1].average_y for d in self.datasets])

class grapherLB(grapher):

	def __init__(self):
		grapher.__init__(self, "len_base_\d+", "LENGTH:")
		for d in self.datasets:
			d.postProcess(False)

		self.point_style_list=['rs-', 'bs-', 'gs-', 'ms-']
		self.xlabel="Length of Base String"
		self.ylabel="Computation Time (Sec)"
		self.x_lower_bound=0
		self.x_upper_bound=max([d.data[-1].x_val for d in self.datasets])
		self.y_lower_bound=0
		self.y_upper_bound=sorted([d.data[-1].average_y for d in self.datasets])[-2] #second largest last y data point

class grapherLF(grapher):

	def __init__(self):
		grapher.__init__(self, "load_factor_\d+", "BINS:")
		for d in self.datasets:
			d.postProcess(lambda x: float(2**self.first_base_string_length)/x)

		self.point_style_list=['gs-', 'ms-']
		self.xlabel="Upper Limit of Load Factor"
		self.ylabel="Computation Time (Sec)"
		self.x_lower_bound=0
		self.x_upper_bound=max([d.data[0].x_val for d in self.datasets])
		self.y_lower_bound=0
		self.y_upper_bound=max([d.data[0].average_y for d in self.datasets])

class grapherWC(grapher):

	def __init__(self):
		grapher.__init__(self, "worst_case_\d+", "LENGTH:")
		self.combineData("worst_case_E_\d+")

		for d in self.datasets:
			d.postProcess(False)

		self.point_style_list=['rs-', 'bs-', 'gs-', 'ms-']
		self.xlabel="Length of Base String and Words in Text File"
		self.ylabel="Computation Time (Sec)"
		self.x_lower_bound=0
		self.x_upper_bound=max([d.data[-1].x_val for d in self.datasets])
		self.y_lower_bound=0
		self.y_upper_bound=sorted([d.data[-1].average_y for d in self.datasets])[-2] #second largest last y data point

def main():
	grapher_path=os.path.dirname(os.path.realpath(__file__))
	cwd_path=os.getcwd()
	os.chdir(os.path.dirname(grapher_path) + "/test_results")
	bob=grapherNW()
	alice=grapherLB()
	chelsea=grapherLF()
	darren=grapherWC()

	bob.chart()
	alice.chart()
	chelsea.chart()
	darren.chart()
	
	os.chdir(cwd_path)

if __name__ == '__main__': main()
	


