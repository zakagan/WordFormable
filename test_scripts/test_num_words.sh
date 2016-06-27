#!/bin/bash
clear

return_dir=`pwd`
cd "${0%/*}"

input_path="../test_files/"
input_name="words"
input_prefix=$input_path$input_name

result_path="../test_results/"
result_name="results_num_words"
extension=".txt"

executable_path="../"

results_file=$result_path$result_name$extension

base_strings=("ougzvhsrwf" "ruyajlwigx" "wwufpxuwrg" "bznpflexir" "hqayyznmxr")

echo "Testing N: file length by word count w/ ten char base strings"  1> $results_file

declare -a ITERATIONS
for num in {0..9}; do 
	ITERATIONS[$num]=$((2**$num))
done

echo "" 1>> $results_file
for string in ${base_strings[@]}; do
	echo $string 1>> $results_file
done
echo "" 1>> $results_file

for executable in WordPercentSort WordPercentTable WordPercentPrecomputeSort WordPercentPrecomputeTable; do

	echo "" 1>> $results_file
	echo "SOLUTION: $executable" 1>> $results_file

	for ((i=0; i<${#ITERATIONS[@]}; i++)); do
		iter_val=ITERATIONS[$i]
		string_var=base_strings[0]

		echo "" 1>> $results_file
		echo "FILE: $input_prefix${!iter_val}$extension" 1>> $results_file
		echo "XWORDS: ${!iter_val}" 1>> $results_file
		echo "$executable_path$executable ${!string_var} $input_prefix${!iter_val}$extension" 1>> $results_file
		(time $executable_path$executable ${!string_var} $input_prefix${!iter_val}$extension) >> $results_file 2>&1
		for ((j=1;j<=4;j++)); do
			string_var=base_strings[$j]
			(time $executable_path$executable ${!string_var} $input_prefix${!iter_val}$extension) 2>> $results_file 1> /dev/null
		done
	done
done

cd $return_dir 