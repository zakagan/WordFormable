#!/bin/bash
clear

return_dir=`pwd`
cd "${0%/*}"

base_string_length=10
base_strings=("ougzvhsrwf" "ruyajlwigx" "wwufpxuwrg" "bznpflexir" "hqayyznmxr")
bucket_max=$(( 1<<(base_string_length+4) ))

input_path="../test_files/"
input_name="words128"
extension=".txt"
input_file=$input_path$input_name$extension

result_path="../test_results/"
result_name="results_load_factor"
results_file=$result_path$result_name$extension

executable_path="../"

echo "Testing load factor"  1> $results_file
echo "Max buckets = $bucket_max" 1>> $results_file
echo "" 1>> $results_file

for string in ${base_strings[@]}; do
	echo $string 1>> $results_file
done

for executable in WordPercentPrecomputeSort WordPercentPrecomputeTable; do

	echo "" 1>> $results_file
	echo "SOLUTION: $executable" 1>> $results_file

	for ((buckets=2;buckets<=$bucket_max;buckets<<1)); do

		echo "" 1>> $results_file
		echo "FILE: $input_file" 1>> $results_file
		echo "BINS: $((buckets-1))" 1>> $results_file
		echo "$executable_path$executable ${base_strings[0]} $input_file $((buckets-1))" 1>> $results_file
		(time $executable_path$executable ${base_strings[0]} $input_file $((buckets-1))) >> $results_file 2>&1
		for ((j=1;j<=4;j++)); do
			(time $executable_path$executable ${base_strings[$j]} $input_file $((buckets-1))) 2>> $results_file 1> /dev/null
		done
	done
done

cd $return_dir 