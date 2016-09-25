import sys, os, re
import matplotlib.pyplot as plt
from datasets import Record, Dataset

def filterDirsByRegex(regex):
	#gnarley list comprehension that gathers a list of dirs from current directory that match a regex
	return [m.group(0) for l in [d for d in os.listdir() if os.path.isdir(d)] for m in [re.search(regex,l)] if m]

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

class Grapher(object):
#object the finds data from test files, processes them into the previous objects, and sets them up to be graphed via matplotlib

	def __init__(self, target_dir, x_var_pattern):
		self.x_var_pattern=x_var_pattern
		self.first_base_string_length=None
		self.first_num_chars=None
		self.first_num_tokens=None
		self.first_num_formable=None
		self.graph_title=None
		self.datasets={}
		
		os.chdir(target_dir)
		#Here the test results files are selected
		temp_dataset_list=[] #new datasets will be placed here
		for idx,file_path in enumerate([f for f in os.listdir() if f.endswith(".txt")]):
			if idx==0:
				try:
					f = open(file_path,'r')
				except OSError as err:
					 print("File could not be opened due to OS error {0}".format(err))
				except:
					print("File could not be opened due to an unexpected error:", sys.exc_info()[0])
					raise
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

			temp_dataset_list.append(self._readData(file_path))
		#check for and combine any duplicate solution datasets into dataset dict datasets
		for d in temp_dataset_list:
			if d.solution in self.datasets:
				self.datasets[d.solution].addRecords(d.data)
			else:
				self.datasets[d.solution]=d

		os.chdir(os.path.dirname(target_dir))

	def _readData(self, file_path):
	#method that actually grabs x and y data from file and processes them into record objects
			data_list=[]
			num_records=0
			x=None
			y=None
			y_vals=[]
			solution=None
			style=None
			attribute_dict={
				"WordFormablePartials":(6,"ro-"), 
				"WordFormableTable":(5,"ko-"), 
				"WordFormablePowerString":(4,"gs-"), 
				"WordFormablePowerVInts":(3,"ms-"),
				"WordFormableQueueSearch":(2,"co-"),
				"WordFormableBinarySearch":(1,"bo-"),  
				## Supporting outdated names of solutions ##
				"WordFormablePowerPC":(4,"gs-"), 
				"WordFormablePowerHP":(3,"ms-"),
				"WordFormableQueue":(2,"co-")	
				}
			try:
				f = open(file_path,'r')
			except OSError as err:
				 print("File could not be opened due to OS error {0}".format(err))
			except:
				print("File could not be opened due to an unexpected error:", sys.exc_info()[0])
				raise
			#Here the files are read and parsed
			for line in f:
				text_list=line.split()
				if not solution and 'SOLUTION:' in line:
					solution=text_list[text_list.index('SOLUTION:')+1]
				elif self.x_var_pattern in line:
					if x is not None and y_vals and None not in y_vals:
						r=Record(x,y_vals)
						data_list.append(r)
						num_records+=1
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
					r=Record(x,y_vals)
					data_list.append(r)
					num_records+=1
					x=None
					y_vals=[]
			f.close()
			order,style=attribute_dict.get(solution, (-1,"kx-"))

			d=Dataset(solution,data_list,num_records,order,style)
			return d

	def combineData(self, associate_dir):
	#method to add data from another folder of test files to the current collection of datasets
		os.chdir(associate_dir)
		#Here the test results files are selected
		for file_path in [f for f in os.listdir() if f.endswith(".txt")]:
			d=self._readData(file_path)
			if d.solution in self.datasets:
				self.datasets[d.solution].addRecords(d.data)
			else:
				self.datasets[d.solution]=d

		os.chdir(os.path.dirname(associate_dir))

	def chart(self):
	#method to prepares charts, this general method is overridded in each subclass
		fig=plt.figure()
		ax1=fig.add_subplot(111)
		for d in sorted(list(self.datasets.values()),key=lambda d: d.order, reverse=True):
			if d.num_records >= 1:
				ax1.plot(d.getXValues(), d.getYValues(), d.style, label=d.solution)
			else:
				del self.datasets[d.solution]
				print("Not enough data present in the {} dataset.".format(d.solution))

		plt.legend(loc='upper left')
		plt.show()

class GrapherNW(Grapher):

	def __init__(self, provided_dirname):
		super().__init__(provided_dirname, "XWORDS:")

	def chart(self):
		fig=plt.figure()
		ax1=fig.add_subplot(111)
		for d in sorted(list(self.datasets.values()),key=lambda d: d.order, reverse=True):
			if d.num_records >= 1:
				d.transformXVals(lambda x: self.first_num_tokens * x)
				ax1.plot(d.getXValues(), d.getYValues(), d.style, label=d.solution)
			else:
				del self.datasets[d.solution]
				print("Not enough data present in the {} dataset.".format(d.solution))

		x_lower_bound=0
		x_upper_bound=max([d.data[-1].x_val for d in self.datasets.values()])
		y_lower_bound=0
		y_upper_bound=max([d.data[-1].average_y for d in self.datasets.values()])
		xlabel="Number of words in text file"
		ylabel="Computation Time (Sec)"

		plt.xlim(x_lower_bound, x_upper_bound)
		plt.ylim(y_lower_bound, y_upper_bound)
		plt.xlabel(xlabel)
		plt.ylabel(ylabel)
		plt.legend(loc='upper left')
		plt.show()

class GrapherLB(Grapher):

	def __init__(self, provided_dirname):
		super().__init__(provided_dirname, "LENGTH:")


	def chart(self):
		fig=plt.figure()
		ax1=fig.add_subplot(111)
		for d in sorted(list(self.datasets.values()),key=lambda d: d.order, reverse=True):
			if d.num_records >= 2:
				ax1.plot(d.getXValues(), d.getYValues(), d.style, label=d.solution)
			else:
				del self.datasets[d.solution]
				print("Not enough data present in the {} dataset.".format(d.solution))

		xlabel="Length of Base String (Characters)"
		ylabel="Computation Time (Sec)"
		x_lower_bound=0
		x_upper_bound=max([d.data[-1].x_val for d in self.datasets.values()]) #max x-value
		y_lower_bound=0

		if len(self.datasets) > 1:
			y_upper_bound=sorted([d.data[-1].average_y for d in self.datasets.values()])[-2] #second largest last y data point
			#note that this may not result in capping y by its partials solution max datum value
		else:
			y_upper_bound=[d.data[-1].average_y for d in self.datasets.values()][0]

		plt.xlim(x_lower_bound,x_upper_bound)
		plt.ylim(y_lower_bound,y_upper_bound)
		plt.xlabel(xlabel)
		plt.ylabel(ylabel)
		plt.legend(loc='upper left')
		plt.show()

class GrapherLF(Grapher):

	def __init__(self, provided_dirname):
		super().__init__(provided_dirname, "BINS:")

	def chart(self):
		fig=plt.figure()
		ax1=fig.add_subplot(111)
		for d in sorted(list(self.datasets.values()),key=lambda d: d.order, reverse=True):
			if d.num_records >= 1:
				d.transformXVals(lambda x: float(2**self.first_base_string_length)/x)
				ax1.plot(d.getXValues(), d.getYValues(), d.style, label=d.solution)
			else:
				del self.datasets[d.solution]
				print("Not enough data present in the {} dataset.".format(d.solution))
		x_lower_bound=min([d.data[-1].x_val for d in self.datasets.values()])
		x_upper_bound=max([d.data[0].x_val for d in self.datasets.values()])
		y_lower_bound=0
		y_upper_bound=max([d.data[0].average_y for d in self.datasets.values()])
		xlabel="Upper Limit of Load Factor"
		ylabel="Computation Time (Sec)"

		plt.xscale('log',basex=2)
		plt.xlim(x_lower_bound,x_upper_bound)
		plt.ylim(y_lower_bound,y_upper_bound)
		plt.xlabel(xlabel)
		plt.ylabel(ylabel)
		plt.legend(loc='upper left')

		plt.show()

class GrapherWC(Grapher):

	def __init__(self, provided_dirname):
		super().__init__(provided_dirname, "LENGTH:")
		if all(len(d.data)<25 for d in list(self.datasets.values())):
			self.extended=False
		else:
			self.extended=True

	def chart(self):
		fig=plt.figure()
		if self.extended and all([(d.num_records > 16) for d in self.datasets.values()]):
			#sets up left hand chart if there is extended data
			ax1=fig.add_subplot(121)
			for d in sorted(list(self.datasets.values()),key=lambda d: d.order, reverse=True):
				ax1.plot(d.getXValues(), d.getYValues(), d.style, label=d.solution)

			xlabel="Length of Base String and Words in Text File (Characters)"
			ylabel="Computation Time (Sec)"				
			x_lower_bound=0
			x_upper_bound=max([d.data[15].x_val for d in self.datasets.values()])
			y_lower_bound=0
			if len(self.datasets) > 1:
				y_upper_bound=sorted([d.data[-1].average_y for d in self.datasets.values()])[-2] #second largest last y data point
			else:
				y_upper_bound=[d.data[-1].average_y for d in self.datasets.values()][0]

			plt.xlim(x_lower_bound,x_upper_bound)
			plt.ylim(y_lower_bound,y_upper_bound)
			plt.xlabel(xlabel)
			plt.ylabel(ylabel)
			plt.legend(loc='upper left')

		if self.extended:
		# Conditionally makes right plot if there is extended data, otherwise sets up one centered plot 
			ax1=fig.add_subplot(122)
		else:
			ax1=fig.add_subplot(111)

		for d in sorted(list(self.datasets.values()),key=lambda d: d.order, reverse=True):
			if d.num_records >= 2:
				ax1.plot(d.getXValues(), d.getYValues(), d.style, label=d.solution)
			else:
				del self.datasets[d.solution]
				print("Not enough data present in the {} dataset.".format(d.solution))

		xlabel="Length of Base String and Words in Text File (Characters)"
		ylabel="Computation Time (Sec)"
		x_lower_bound=0
		x_upper_bound=max([d.data[-1].x_val for d in self.datasets.values()])
		y_lower_bound=0

		if len(self.datasets) > 1:
			y_upper_bound=sorted([d.data[-1].average_y for d in self.datasets.values()])[-2] #second largest last y data point
		else:
			y_upper_bound=[d.data[-1].average_y for d in self.datasets.values()][0]
		
		plt.xlim(x_lower_bound,x_upper_bound)
		plt.ylim(y_lower_bound,y_upper_bound)
		plt.xlabel(xlabel)
		plt.ylabel(ylabel)
		plt.legend(loc='upper left')

		plt.show()

def main():
	grapher_path=os.path.dirname(os.path.realpath(__file__))
	cwd_path=os.getcwd()
	os.chdir(os.path.dirname(grapher_path) + "/test_results")

	most_recent_NW=GrapherNW(os.path.realpath(filterDirsByRegex("num_words_\d+")[-1]))

	most_recent_LB=GrapherLB(os.path.realpath(filterDirsByRegex("len_base_\d+")[-1]))

	most_recent_LF=GrapherLF(os.path.realpath(filterDirsByRegex("load_factor_\d+")[-1]))

	most_recent_WC=GrapherWC(os.path.realpath(filterDirsByRegex("worst_case_\d+")[-1]))
	most_recent_WC.combineData(os.path.realpath(filterDirsByRegex("worst_case_E_\d+")[-1]))

	most_recent_NW.chart()
	most_recent_LB.chart()
	most_recent_LF.chart()
	most_recent_WC.chart()

	os.chdir(cwd_path)

if __name__ == '__main__': main()
	


