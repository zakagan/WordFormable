import sys, os
from PlotTestResults import filterDirsByRegex, GrapherNW, GrapherLB, GrapherLF, GrapherWC

def indexedDictFromList(provided_list):
	output_dict={}
	for idx,item in enumerate(provided_list):
		output_dict[idx+1]=item
	return output_dict

def menuFromDict(menu_dict,message_str=None):
	if message_str:
		print(message_str)
	keys_list=sorted(list(menu_dict.keys()),reverse=False)
	for key in keys_list:
		print("{0}{1}".format(str(key).ljust(5), menu_dict[key]))

def menuSelect():
	selection=input("Please Select: ")
	if selection in ["q", "Q", "quit", "Quit", "exit"]:
		return "q"
	try:
		return int(selection)
	except ValueError:
		return False
	except:
		print("Input could not be read due to an unexpected error:", sys.exc_info()[0])
		raise

def grapherMenu(grapher_subclass, dirname_regex, graph_name=""):
	print("\nChoose data to add the", graph_name, "graph:")
	test_dict=indexedDictFromList(filterDirsByRegex(dirname_regex)+["Plot Data!", "Return to main menu"])
	intialized_bool=False
	display_menu_bool=True
	num_options=len(test_dict)
	while True:
		if display_menu_bool:
			menuFromDict(test_dict)
		selection=menuSelect()
		if selection in test_dict.keys() and selection<num_options-1:
			dir_path=test_dict.pop(selection, None)
			display_menu_bool=True
			if not intialized_bool:
				current_grapher=grapher_subclass(os.path.realpath(dir_path))
				intialized_bool=True
			else:
				current_grapher.combineData(os.path.realpath(dir_path))
		elif intialized_bool and selection==num_options-1:
			current_grapher.chart()
			break
		elif selection==num_options:
			break
		elif selection=="q":
			os.chdir(cwd_path)
			sys.exit("Quitting...")	
		else:
			display_menu_bool=False
			print("Invalid imput provided.")

def main():

	main_menu_dict={
		1: "...the number of words in text file [NW]",
		2: "...the length of the base string [LB]",
		3: "...the load factor of hash function solutions [LF]",
		4: "...the worst case length of average word in file & length of base string [WC]",
		5: "Quit",
	}
	display_menu_bool=True
	while True:
		if display_menu_bool:
			menuFromDict(main_menu_dict,"\nPlot time effciency over...")
		selection=menuSelect()
		if selection==1:
			grapherMenu(GrapherNW, "num_words_\d+", "Number of Words")
			display_menu_bool=True
		elif selection==2:
			grapherMenu(GrapherLB, "len_base_\d+", "Length of Base")
			display_menu_bool=True
		elif selection==3:
			grapherMenu(GrapherLF, "load_factor_\d+", "Load Factor")
			display_menu_bool=True
		elif selection==4:
			grapherMenu(GrapherWC, "worst_case_\w+", "Worst Case")
			display_menu_bool=True
		elif selection==5 or selection=="q":
			print("Quitting")
			break
		else:
			print("Invalid imput provided.")
			display_menu_bool=False

if __name__ == '__main__': 
	grapher_path=os.path.dirname(os.path.realpath(__file__))
	cwd_path=os.getcwd()
	os.chdir(os.path.dirname(grapher_path) + "/test_results")
	main()
	os.chdir(cwd_path)