#!/bin/bash

return_dir=`pwd`
cd "${0%/*}"

time_stamp=`date +%Y-%m-%d__%H_%M_%S`

extension=".txt"

input_path="../test_files/words/"
input_name="words"
input_prefix=$input_path$input_name

results_path="../test_results/"
mkdir -p $results_path
results_path="${results_path}num_words_"
results_prefix="results_NW_"
results_suffix="_${time_stamp}${extension}"

executable_path="../"
executables=("WordFormablePartials" "WordFormableTable" "WordFormablePowerPC" "WordFormablePowerHP")

base_strings=()
for ((i=1;i<=5;i++)); do
	base_strings+=("$(env LC_CTYPE=C tr -dc "a-z" < /dev/urandom | head -c 10)")
done

declare -a ITERATIONS
for num in {0..9}; do 
	ITERATIONS[$num]=$((2**$num))
done

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
	echo "Testing N: file length by word count w/ ten char base strings"  1> $results_file
	echo "SOLUTION: $executable" 1>> $results_file
	echo "FILE: $results_file" 1>> $results_file
	echo "" 1>> $results_file
	echo "Base strings:" 1>> $results_file
	for string in ${base_strings[@]}; do
		echo $string 1>> $results_file
	done
done

#Tests
for iter_val in ${ITERATIONS[@]}; do
	input_file=$input_prefix$iter_val$extension
	echo "Testing on ${input_file}"
	for executable in ${executables[@]}; do
		results_file=$results_path$results_prefix$executable$results_suffix
		echo "" 1>> $results_file
		echo "XWORDS: $iter_val" 1>> $results_file
		echo "time $executable_path$executable ${base_strings[0]} $input_file 1" 1>> $results_file
		(time $executable_path$executable ${base_strings[0]} $input_file 1) >> $results_file 2>&1
		for ((j=1;j<=4;j++)); do
			(time $executable_path$executable ${base_strings[$j]} $input_file 1) 2>> $results_file 1> /dev/null
		done
	done
done

cd $return_dir 