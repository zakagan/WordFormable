#!/bin/bash

return_dir=`pwd`
cd "${0%/*}"

time_stamp=`date +%Y-%m-%d__%H_%M_%S`

extension=".txt"

input_path="../test_files/words/"
input_name="words512"
input_file=$input_path$input_name$extension

results_path="../test_results/"
mkdir -p $results_path
results_path="${results_path}load_factor_"
results_prefix="results_LF_"
# results_suffix="_${time_stamp}${extension}"
results_suffix="_${extension}"

executable_path="../"
executables=("WordFormablePowerPC" "WordFormablePowerHP")

base_strings=("ougzvhsrwf" "ruyajlwigx" "wmofpxunrg" "bznpflexir" "hqajyznmxr") #random strings purged of repeating chars
base_string_length=10
bucket_max=$(( 1<<(base_string_length+4) ))

# n=0
# results_path_attempt="${results_path}${n}/"
# while ! mkdir "$results_path_attempt"  2> /dev/null; do
# 	n=$((n+1))
# 	results_path_attempt="${results_path}${n}/"
# done
# results_path=$results_path_attempt
results_path="${results_path}${time_stamp}/"
mkdir "$results_path"

#Header
for executable in ${executables[@]}; do
	results_file=$results_path$results_prefix$executable$results_suffix
	echo "Testing load factor"  1> $results_file
	echo "SOLUTION: $executable" 1>> $results_file
	echo "FILE: $results_file" 1>> $results_file
	echo "Max buckets = $bucket_max" 1>> $results_file
	echo "" 1>> $results_file
	for string in ${base_strings[@]}; do
		echo $string 1>> $results_file
	done
done

#Tests
for ((buckets=2;buckets<=$bucket_max;buckets=$buckets<<1)); do
	true_buckets=$((buckets-1))
	echo "Testing with $true_buckets buckets"
	for executable in ${executables[@]}; do
		results_file=$results_path$results_prefix$executable$results_suffix
		n=0
		while [ -e "$results_file" ]; then
			n=$((n+1))
			results_file=$results_path$results_prefix$executable$n$results_suffix
		echo "" 1>> $results_file
		echo "BINS: $true_buckets" 1>> $results_file
		echo "time $executable_path$executable ${base_strings[0]} $input_file 1 $true_buckets" 1>> $results_file
		(time $executable_path$executable ${base_strings[0]} $input_file 1 $true_buckets) >> $results_file 2>&1
		for ((j=1;j<=4;j++)); do
			(time $executable_path$executable ${base_strings[$j]} $input_file 1 $true_buckets) 2>> $results_file 1> /dev/null
		done
	done	
done

cd $return_dir 