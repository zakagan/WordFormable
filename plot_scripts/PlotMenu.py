import sys, os
from PlotTestResults import filterDirsByRegex, GrapherNW, GrapherLB, GrapherLF, GrapherWC

def menuFromList(menu_list,message_str=None):
	if message_str:
		print(message_str)
	for idx,entry in enumerate(menu_list):
		print(idx, entry)

def menuSelect():
	selection=input("Please Select: ")
	try:
		return int(selection)
	except ValueError:
		return False
	except:
		print("Input could not be read due to an unexpected error:", sys.exc_info()[0])
		raise

def grapherMenu(grapher_subclass, dirname_regex, graph_name=""):
	print("Choose data to add the", graph_name, "graph:")
	test_list=filterDirsByRegex(dirname_regex)
	test_list+=["Plot Data!", "Return to main menu"]
	intialized_bool=False
	display_menu_bool=True
	while True:
		num_options=len(test_list)
		if display_menu_bool:
			menuFromList(test_list)
		selection=menuSelect()
		if selection in range(0,num_options-1) and selection<num_options-2:
			dir_path=test_list.pop(selection)
			display_menu_bool=True
			if not intialized_bool:
				current_grapher=grapher_subclass(os.path.realpath(dir_path))
				intialized_bool=True
			else:
				current_grapher.combineData(os.path.realpath(dir_path))
		elif intialized_bool and selection==num_options-2:
			current_grapher.chart()
			break
		elif selection==num_options-1:
			break
		else:
			display_menu_bool=False
			print("Invalid imput provided.")

def main():
	grapher_path=os.path.dirname(os.path.realpath(__file__))
	cwd_path=os.getcwd()
	os.chdir(os.path.dirname(grapher_path) + "/test_results")

	main_menu_list=[
		"... the number of words in text file [NW]",
		"... the length of the base string [LB]",
		"... the load factor of hash function solutions [LF]",
		"... the worst case length of average word in file & length of base string [WC]",
		"Quit"
	]
	display_menu_bool=True
	while True:
		if display_menu_bool:
			menuFromList(main_menu_list,"Plot time effciency over...")
		selection=menuSelect()
		if selection==0:
			grapherMenu(GrapherNW, "num_words_\d+", "Number of Words")
			display_menu_bool=True
		elif selection==1:
			grapherMenu(GrapherLB, "len_base_\d+", "Length of Base")
			display_menu_bool=True
		elif selection==2:
			grapherMenu(GrapherLF, "load_factor_\d+", "Load Factor")
			display_menu_bool=True
		elif selection==3:
			grapherMenu(GrapherWC, "worst_case_\w+", "Worst Case")
			display_menu_bool=True
		elif selection==4:
			print("Quitting")
			break
		else:
			print("Invalid imput provided.")
			display_menu_bool=False

	os.chdir(cwd_path)

if __name__ == '__main__': main()