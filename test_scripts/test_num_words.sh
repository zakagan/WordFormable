#!/bin/bash
clear

return_dir=pwd
cd "${0%/*}"

input_path="../test_files/"
input_name="words"
input_prefix=$input_path$input_name

result_path="../test_results/"
result_name="results_num_words"
extension=".txt"

results_file=$result_path$result_name$extension

base_strings=("ougzvhsrwf" "ruyajlwigx" "wwufpxuwrg" "bznpflexir" "hqayyznmxr")

echo "Testing N: file length by word count w/ ten char base strings"  1> $results_file

echo "" 1>> $results_file
for string in ${base_strings[@]}; do
	echo $string 1>> $results_file
done
echo "" 1>> $results_file

for executable in ./WordPercentSort ./WordPercentTable ./WordPercentPrecomputeSort ./WordPercentPrecomputeTable; do

	echo "" 1>> $results_file
	echo "$executable" 1>> $results_file

	for i in "" "2" "4" "8" "16" "32" "64" "128" "256" "512"; do

		echo "" 1>> $results_file
		echo "file: $input_prefix$i$extension" 1>> $results_file
		echo "" 1>> $results_file

		array_var=base_strings[0]
		(time $executable ${!array_var} $input_prefix$i$extension) >> $results_file 2>&1
		for ((j=1;j<=4;j++)); do
			array_var=base_strings[$j]
			(time $executable ${!array_var} $input_prefix$i$extension) 2>> $results_file 1> /dev/null
		done
	done
done

cd return_dir 