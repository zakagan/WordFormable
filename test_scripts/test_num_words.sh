#!/bin/bash
clear

path="../test_results/"
file_name="results_num_words.txt"

base_strings=("ougzvhsrwf" "ruyajlwigx" "wwufpxuwrg" "bznpflexir" "hqayyznmxr")

touch $path$file_name

echo "Testing N: file length by word count w/ ten char base strings"  1> $path$file_name

echo "" 1>> $path$file_name
for string in ${base_strings[@]}; do
	echo $string 1>> $path$file_name
done
echo "" 1>> $path$file_name

for executable in ./WordPercentSort ./WordPercentTable ./WordPercentPrecomputeSort ./WordPercentPrecomputeTable; do

	echo "" 1>> $path$file_name
	echo "$executable" 1>> $path$file_name

	for i in "" "2" "4" "8" "16" "32" "64" "128" "256" "512"; do

		echo "" 1>> $path$file_name
		echo "file: words$i" 1>> $path$file_name
		echo "" 1>> $path$file_name

		array_var=base_strings[0]
		(time $executable ${!array_var} words$i.txt) >> $path$file_name 2>&1
		for j in {1..4}; do
			array_var=base_strings[$j]
			(time $executable ${!array_var} words$i.txt) 2>> $path$file_name 1> /dev/null
		done
	done
done
