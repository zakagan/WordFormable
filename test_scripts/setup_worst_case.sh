#!/bin/bash

return_dir=`pwd`
cd "${0%/*}"

path="../test_files/worst_case/"
name="worst_case"
extension=".txt"
prefix=$path$name

if [ ! -d "$path" ]; then
  mkdir -p "$path"
fi

test_quotes="\"\""
test_str="zyxwvutsrqponmlkjihgfedcba9876543210-ZYXWVUTSRQPONMLKJIHGFEDCBA"

temp_name="temp"
temp_file=$path$temp_name$extension

WC_STR_LEN=()
if [ "${1:0:1}" = "e" ] || [ "${1:0:1}" = "E" ]; then
	# Test string lengths for the extended worst case scenario
	for ((i=30;i<=63;i+=6)); do 
		WC_STR_LEN+=($i)
	done
	WC_STR_LEN+=(63)
elif [ "${1:0:1}" = "i" ] || [ "${1:0:1}" = "I" ]; then
	# Test string lengths for the intermediate worst case scenario (connecting non-extended and extended cases)
	for ((i=25;i<=29;i+=1)); do 
		WC_STR_LEN+=($i)
	done
	WC_STR_LEN+=(32)
	WC_STR_LEN+=(34)
else
	for ((i=0;i<=24;i+=1)); do 
	# Test string lengths for the intial 0 to 24 string length range 
		WC_STR_LEN+=($i)
	done
fi

for len in ${WC_STR_LEN[@]}; do
	current_file=$prefix$len$extension
	if [ $len = 0 ]; then
		current_str=$test_quotes
	else
		current_str=${test_str:0:$len}
	fi

	echo $current_str > $current_file
	for ((j=0;j<=24;j++)); do
		cat $current_file > $temp_file
		cat $temp_file >> $current_file
	done
done
rm $temp_file

cd $return_dir