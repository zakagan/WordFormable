#! /bin/bash
clear

file_name="results_num_words.txt"

base_strings=("ougzvhsrwf" "ruyajlwigx" "wwufpxuwrg" "bznpflexir" "hqayyznmxr")

touch $file_name

echo "Testing N: file length by word count w/ ten char base strings"  1> $file_name

echo "" 1>> $file_name
for string in "${base_strings[@]}"; do
	echo $string 1>> $file_name
done
echo "" 1>> $file_name

for executable in ./WordPercentSort ./WordPercentTable ./WordPercentPrecomputeSort ./WordPercentPrecomputeTable; do

	echo "" 1>> $file_name
	echo "$executable" 1>> $file_name

	for i in "" "2" "4" "8" "16" "32" "64" "128" "256" "512"; do

		echo "" 1>> $file_name
		echo "file: words$i" 1>> $file_name
		echo "" 1>> $file_name

		(time $executable ${base_strings[0]} words$i.txt) >> $file_name 2>&1
		(time $executable ${base_strings[1]} words$i.txt) 2>> $file_name 1> /dev/null
		(time $executable ${base_strings[2]} words$i.txt) 2>> $file_name 1> /dev/null
		(time $executable ${base_strings[3]} words$i.txt) 2>> $file_name 1> /dev/null
		(time $executable ${base_strings[4]} words$i.txt) 2>> $file_name 1> /dev/null
	done
done
