#!/bin/bash
clear

return_dir=pwd
cd "${0%/*}"

input_path="../test_files/"
input_name="words256"
extension=".txt"
input_file=$input_path$input_name$extension

result_path="../test_results/"
result_name="results_load_factor"
results_file=$result_path$result_name$extension

base_strings=("ougzvhsrwf" "ruyajlwigx" "wwufpxuwrg" "bznpflexir" "hqayyznmxr")


echo "Testing load factor: base string length"  1> $results_file
echo "" 1>> $results_file

echo "" 1>> $results_file
for string in ${base_strings[@]}; do
	echo $string 1>> $results_file
done
echo "" 1>> $results_file


for executable in ./WordPercentPrecomputeSort ./WordPercentPrecomputeTable; do

	echo "" 1>> $results_file
	echo "$executable" 1>> $results_file

	for ((buckets=2;buckets<=4096;buckets=buckets<<1)); do

		echo "" 1>> $results_file
		echo "num of bins: $buckets" 1>> $results_file
		echo "" 1>> $results_file

		array_var=base_strings[0]
		(time $executable ${!array_var} $input_file (($buckets-1))) >> $results_file 2>&1
		for ((j=1;j<=4;j++)); do
			array_var=base_strings[$j]
			(time $executable ${!array_var} $input_file (($buckets-1))) 2>> $results_file 1> /dev/null
		done
	done
done

cd $return_dir 