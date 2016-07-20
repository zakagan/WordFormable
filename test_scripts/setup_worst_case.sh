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
if [ "${1:0:1}" != "e" ] && [ "${1:0:1}" != "E" ]; then
	for ((i=0;i<=24;i+=2)); do 
		WC_STR_LEN+=($i)
	done
else
	for ((i=25;i<=60;i+=5)); do 
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