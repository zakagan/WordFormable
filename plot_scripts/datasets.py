
class Record(object):
# Basic data object that contains x value and a collection of y values to be averaged
	def __init__(self, x_val, y_val_list):
		self.x_val=x_val
		self.y_val_list=y_val_list
		self._average_y=False
		#All values stored as floats

	def yConcat(self, new_y_list):
		self._average_y=False
		self.y_val_list+=new_y_list

	@property
	def average_y(self):
		if self._average_y:
			return self._average_y
		elif self.y_val_list:
			self._average_y=(sum(self.y_val_list)/ len(self.y_val_list))
			return self._average_y
		else:
			raise AttributeError("No y data is present from which to generate values: y_val_list = {0!r}".format(self.y_val_list))

class Dataset(object):
# object containing a collection of records that correspond to one solution, and more generally one particular tests sequence

	def __init__(self, solution, record_list=[], num_records=0, order=0, style="ko-"):
		self.solution=solution
		self.data=record_list
		self.num_records=num_records
		self.order=order
		self.style=style

	def addRecords(self, new_record_list):
		ridx=0     #running index of older records
		for new_record in new_record_list:
			while ridx <= self.num_records-1:
				if new_record.x_val > self.data[ridx].x_val and ridx!=self.num_records-1:
					ridx+=1
					continue
				elif new_record.x_val == self.data[ridx].x_val:
					# combines y vals for a single x val together into the same record
					self.data[ridx].yConcat(new_record.y_val_list)
					ridx+=1
					break
				elif new_record.x_val < self.data[ridx].x_val:
					self.data.insert(ridx,new_record)
					ridx+=1
					self.num_records+=1
					break
				else:
					# must be at end of list
					self.data.insert(ridx+1,new_record)
					ridx+=1
					self.num_records+=1
					break

	def transformXVals(self, func):
		for record in self.data:
			record.x_val=func(record.x_val)

	def getXValues(self):
		return [d.x_val for d in self.data]

	def getYValues(self):
		return [d.average_y for d in self.data]
