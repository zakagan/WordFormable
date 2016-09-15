 #!/bin/bash

return_dir=`pwd`
cd "${0%/*}"

time_stamp=`date +%Y-%m-%d__%H_%M_%S`

extension=".txt"

input_path="../test_files/worst_case/"
input_name="worst_case"
input_prefix=$input_path$input_name

results_path="../test_results/"
mkdir -p $results_path
results_path="${results_path}worst_case_"
results_prefix="results_WC_"
# results_suffix="_${time_stamp}${extension}"
results_suffix="_${extension}"
RF_ARRAY=()

executable_path="../"
EXEC_ARRAY=("WordFormablePartials" "WordFormableTable" "WordFormablePowerString" "WordFormablePowerVInts" "WordFormableQueueSearch" "WordFormableBinarySearch")

single_executable=$2
if [ -n $single_executable ] && [ $single_executable -ge "0" -a $single_executable -le "5" ]; then
	EXEC_ARRAY=("${EXEC_ARRAY[@]:$single_executable:1}")
fi

test_str="zyxwvutsrqponmlkjihgfedcba9876543210ZYXWVUTSRQPONMLKJIHGFEDCBA"  		#62 chars long
padding_str=".............................................................."	#also 62 chars

WC_LEN_ARRAY=()
case $1 in
	0)
		for ((i=0;i<=11;++i)); do 
			WC_LEN_ARRAY+=($i)
		done
		;;
	1)
		for ((i=12;i<=23;++i)); do 
			WC_LEN_ARRAY+=($i)
		done
		;;
	2)
		for ((i=24;i<=35;++i)); do 
			WC_LEN_ARRAY+=($i)
		done
		;;
	3)
		for ((i=36;i<=58;i+=2)); do 
			WC_LEN_ARRAY+=($i)
		done
		WC_LEN_ARRAY+=(61)
		;;
	*)
		echo "Use an integer input (0, 1, 2, or 3) to select which set of worst case files to test on"
		;;
esac 

# if [ "${1:0:1}" = "e" ] || [ "${1:0:1}" = "E" ]; then
# 	# Test specifics for the extended worst case scenario
# 	results_path="${results_path}E_"
# 	results_prefix="${results_prefix}E_"
# 	EXEC_ARRAY=("${EXEC_ARRAY[@]:0:2}" "${EXEC_ARRAY[@]:4:1}")
# 	for ((i=30;i<=63;i+=6)); do 
# 		WC_LEN_ARRAY+=($i)
# 	done
# 	WC_LEN_ARRAY+=(63)
# elif [ "${1:0:1}" = "i" ] || [ "${1:0:1}" = "I" ]; then
# 	# Test specifics for the intermediate (partially extended) worst case scenario
# 	results_path="${results_path}I_"
# 	results_prefix="${results_prefix}I_"
# 	EXEC_ARRAY=("${EXEC_ARRAY[@]:0:2}" "${EXEC_ARRAY[@]:3:2}")
# 	for ((i=25;i<=29;i+=1)); do 
# 		WC_LEN_ARRAY+=($i)
# 	done
# 	WC_LEN_ARRAY+=(32)
# 	WC_LEN_ARRAY+=(34)
# else
# 	# Non extended specifics, just a range of 0 to 24 length base strings / averag length in file
# 	for ((i=0;i<=24;i+=1)); do 
# 		WC_LEN_ARRAY+=($i)
# 	done
# fi

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
	echo "Testing K & M: worst case string lengths"  1> $results_file
	echo "SOLUTION: $executable" 1>> $results_file
	echo "FILE: $input_file" 1>> $results_file
	echo ""  1>> $results_file
	echo "string used for testing: $test_str" 1>> $results_file
done

#Tests
for len in ${WC_LEN_ARRAY[@]}; do
	echo "Testing WC file with length $len"
	input_file=$input_prefix$len$extension

	#Removes power set solutions if the length passes a threshold
	if [ $len -ge 30 ] && [ -z $single_executable ]; then
		if  [ ${#EXEC_ARRAY[@]} -gt 5 ]; then
			EXEC_ARRAY=("${EXEC_ARRAY[@]:0:2}" "${EXEC_ARRAY[@]:4:2}")
		# elif [ ${#EXEC_ARRAY[@]} -gt 3 ]; then
		# 	EXEC_ARRAY=("${EXEC_ARRAY[@]:0:2}" "${EXEC_ARRAY[@]:3:1}")
		fi
	fi
	
	# excutes tests and saves them to their respective files
	if [ $((len%2)) -eq 0 ]; then
		current_str=${padding_str:0:$pad_len}${test_str:0:$len}${padding_str:0:$pad_len}
	else 
		current_str=${padding_str:0:$pad_len}${test_str:0:$len}${padding_str:0:$((pad_len+1))} 
	fi
	for  ((i=0; i<${#EXEC_ARRAY[@]}; ++i)); do
		echo "" 1>> ${RF_ARRAY[$i]}
		echo "LENGTH: $len" 1>> ${RF_ARRAY[$i]}
		echo "time $executable_path${EXEC_ARRAY[$i]} $current_str $input_file 1" 1>> ${RF_ARRAY[$i]}
		(time $executable_path${EXEC_ARRAY[$i]} $current_str $input_file 1) >> ${RF_ARRAY[$i]} 2>&1
		for ((j=1;j<=4;++j)); do
			(time $executable_path${EXEC_ARRAY[$i]} $current_str $input_file 1) 2>> ${RF_ARRAY[$i]} 1> /dev/null
		done
	done
done

cd $return_dir