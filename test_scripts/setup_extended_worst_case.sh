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

EWC_STR_LEN=()
for ((i=25;i<=60;i+=5)); do 
	WC_STR_LEN+=($i)
done

for len in ${EWC_STR_LEN[@]}; do
	current_file=$prefix$len$extension
	if [ $len = 0 ]; then
		current_str=$test_quotes
	else
		current_str=${test_str:0:$len}
	fi

	echo $current_str > $current_file
	for ((j=0;j=<24;j++)); do
		cat $current_file > $temp_file
		cat $temp_file >> $current_file
	done
done
rm $temp_file

cd $return_dir