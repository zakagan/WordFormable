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
results_path="${results_path}len_base_"
results_prefix="results_LB_"
# results_suffix="_${time_stamp}${extension}"
results_suffix="_${extension}"
RF_ARRAY=()

executable_path="../"
EXEC_ARRAY=("WordFormablePartials" "WordFormableTable" "WordFormablePowerString" "WordFormablePowerVInts" "WordFormableQueueSearch" "WordFormableBinarySearch")

single_executable=$1
if [ -n "$single_executable" ] && [ "$single_executable" -ge "0" -a "$single_executable" -le "5" ]; then
	EXEC_ARRAY=("${EXEC_ARRAY[@]:$single_executable:1}")
fi

base_null=("\"\"" "\"\"" "\"\"" "\"\"" "\"\"")
base_strings=()
for ((i=1;i<=5;i++)); do
	base_strings+=("$(env LC_CTYPE=C tr -dc "a-z" < /dev/urandom | head -c 26)")
done

BASE_STR_LEN=()
for ((i=0;i<=26;i+=2)); do 
	BASE_STR_LEN+=($i)
done

# n=0
# results_path_attempt="${results_path}${n}/"
# while ! mkdir "$results_path_attempt" 2> /dev/null; do
# 	n=$((n+1))
# 	results_path_attempt="${results_path}${n}/"
# done
# results_path=$results_path_attempt
results_path="${results_path}${time_stamp}/"
mkdir "$results_path"

#Header
for executable in ${EXEC_ARRAY[@]}; do
	results_file=$results_path$results_prefix$executable$results_suffix
	n=0
	while [ -e "$results_file" ]; do
		n=$((n+1))
		results_file=$results_path$results_prefix$executable$n$results_suffix
	done
	RF_ARRAY+=($results_file)
	echo "Testing K: base string length"  1> $results_file
	echo "SOLUTION: $executable" 1>> $results_file
	echo "FILE: $input_file" 1>> $results_file
	echo ""  1>> $results_file
	echo "Base strings:"  1>> $results_file
	for string in $base_strings; do
		echo $string 1>> $results_file
	done	
done

#Tests
for len in ${BASE_STR_LEN[@]}; do
	echo "Testing with base string length $len"
	if [ $len = 0 ]; then
		array_var=("${base_null[@]}")
		index=2
	else
		array_var=("${base_strings[@]}")
		index=$len
	fi
	for ((i=0; i<${#EXEC_ARRAY[@]}; ++i)) do
		echo "" 1>> ${RF_ARRAY[$i]}
		echo "LENGTH: $len" 1>> ${RF_ARRAY[$i]}
		echo "time $executable_path${EXEC_ARRAY[$i]} ${array_var[0]:0:$index} $input_file 1" 1>> ${RF_ARRAY[$i]}
		(time $executable_path${EXEC_ARRAY[$i]} ${array_var[0]:0:$index} $input_file 1) >> ${RF_ARRAY[$i]} 2>&1
		for ((j=1;j<=4;++j)); do
			(time $executable_path${EXEC_ARRAY[$i]} ${array_var[$j]:0:$index} $input_file 1) 2>> ${RF_ARRAY[$i]} 1> /dev/null
		done
	done
done

cd $return_dir 
