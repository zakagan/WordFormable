 #!/bin/bash

return_dir=`pwd`
cd "${0%/*}"

time_stamp=`date +%Y-%m-%d__%H_%M_%S`

extension=".txt"

input_path="../test_files/worst_case/"
input_name="worst_case"
input_prefix=$input_path$input_name

results_path="../test_results/"
mkdir -p $results_path
results_path="${results_path}worst_case_"
results_prefix="results_WC_"
results_suffix="_${time_stamp}${extension}"

executable_path="../"
executables=("WordFormablePartials" "WordFormableTable" "WordFormablePowerPC" "WordFormablePowerHP")

test_quotes="\"\""
test_str="zyxwvutsrqponmlkjihgfedcba9876543210-ZYXWVUTSRQPONMLKJIHGFEDCBA"

WC_STR_LEN=()
if [ "${1:0:1}" = "e" ] || [ "${1:0:1}" = "E" ]; then
	# Test specifics for the extended worst case scenario
	results_path="${results_path}E_"
	results_prefix="${results_prefix}E_"
	executables=("WordFormablePartials" "WordFormableTable")
	for ((i=30;i<=63;i+=6)); do 
		WC_STR_LEN+=($i)
	done
	WC_STR_LEN+=(63)
elif [ "${1:0:1}" = "i" ] || [ "${1:0:1}" = "I" ]; then
	# Test specifics for the intermediate (partially extended) worst case scenario
	results_path="${results_path}I_"
	results_prefix="${results_prefix}I_"
	executables=("WordFormablePartials" "WordFormableTable" "WordFormablePowerHP")
	for ((i=25;i<=29;i+=1)); do 
		WC_STR_LEN+=($i)
	done
	WC_STR_LEN+=(63)
else
	# Non extended specifics, just a range of 0 to 24 length base strings / averag length in file
	for ((i=0;i<=24;i+=1)); do 
		WC_STR_LEN+=($i)
	done
fi

n=0
results_path_attempt="${results_path}${n}/"
while ! mkdir "$results_path_attempt" 2> /dev/null; do
	n=$((n+1))
	results_path_attempt="${results_path}${n}/"
done
results_path=$results_path_attempt

#Header
for executable in ${executables[@]}; do
	results_file=$results_path$results_prefix$executable$results_suffix
	echo "Testing K & M: worst case string lengths"  1> $results_file
	echo "SOLUTION: $executable" 1>> $results_file
	echo "FILE: $input_file" 1>> $results_file
	echo ""  1>> $results_file
	echo "string used for testing: $test_str" 1>> $results_file
done

#Tests
for len in ${WC_STR_LEN[@]}; do
	#Removes power set solutions if the length passes a threshold
	if [ $len -ge 30 ] && [ ${#executables[@]} -gt 2]; then
		executables=("${executables[@]:0:2}")
	fi
	# excutes tests and saves them to their respective files
	echo "Testing WC file with length $len"
	input_file=$input_prefix$len$extension
	if [ $len = 0 ]; then
		current_str=$test_quotes
	else
		current_str=${test_str:0:$len}
	fi
	for executable in ${executables[@]}; do
		results_file=$results_path$results_prefix$executable$results_suffix
		echo "" 1>> $results_file
		echo "LENGTH: $len" 1>> $results_file
		echo "time $executable_path$executable $current_str $input_file 1" 1>> $results_file
		(time $executable_path$executable $current_str $input_file 1) >> $results_file 2>&1
		for ((j=1;j<=4;j++)); do
			(time $executable_path$executable $current_str $input_file 1) 2>> $results_file 1> /dev/null
		done
	done
done

cd $return_dir