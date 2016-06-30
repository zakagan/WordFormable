#!/bin/bash

return_dir=`pwd`
cd "${0%/*}"

input_path="../test_files/worst_case/"
input_name="worst_case"
extension=".txt"
input_prefix=$input_path$input_name

result_path="../test_results/"
result_name="results_worst_case"
results_file=$result_path$result_name$extension

executable_path="../"

if [ ! -d "$result_path" ]; then
  mkdir -p "$result_path"
fi

worst_case_array[0]="\"\""
worst_case_array[2]="ov"
worst_case_array[4]="agD3"
worst_case_array[6]="wgqJa2"
worst_case_array[8]="Ky7tJ46c"
worst_case_array[10]="EMCQdZ3klS"
worst_case_array[12]="4ClbGRUzEskb"
worst_case_array[14]="A1GYMKYgDBcabv"
worst_case_array[16]="0oEBDmSijxKcOLUR"
worst_case_array[18]="5N6cUHil5gSwpvquYL"
worst_case_array[20]="9VWyrpuWvgLzE5v7Tu0t"
worst_case_array[22]="QdjnttnvPq6CwtorpdqnZl"
worst_case_array[24]="AucL8asugf8sNOTGZ5YyrZ6v"
worst_case_array[26]="GI8KPcXVL5lPcxoxVUoeg0PZK7"


echo "Testing K & M: worst case string lengths"  1> $results_file
echo "" 1>> $results_file

for ((i=0;i<=26;i+=2)); do
	echo ${worst_case_array[$i]} 1>> $results_file
done

for executable in WordPercentSort WordPercentTable WordPercentPrecomputeSort WordPercentPrecomputeTable; do

	echo "" 1>> $results_file
	echo "SOLUTION: $executable" 1>> $results_file

	for ((i=0;i<=26;i+=2)); do
		input_file=$input_prefix$i$extension
		echo "" 1>> $results_file
		echo "FILE: $input_file" 1>> $results_file
		echo "LENGTH: $i" 1>> $results_file
		array_var=worst_case_array[$i]
		echo "$executable_path$executable ${!array_var} $input_file" 1>> $results_file
		(time $executable_path$executable ${!array_var} $input_file) >> $results_file 2>&1
		for ((j=1;j<=4;j++)); do
			(time $executable_path$executable ${!array_var} $input_file) 2>> $results_file 1> /dev/null
		done
	done
done

cd $return_dir