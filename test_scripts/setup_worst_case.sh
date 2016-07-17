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
test_str="Zx8wV2Ts3qP4Nm5kJ6Hg7eD1Ba"

temp_name="temp"
temp_file=$path$temp_name$extension
for ((i=0;i<=26;i+=2)); do
	current_file=$prefix$i$extension
	if [ $i = 0 ]; then
		current_str=$test_quotes
	else
		current_str=${test_str:0:$i}
	fi

	echo $current_str > $current_file
	for ((j=0;j<26;j++)); do
		cat $current_file > $temp_file
		cat $temp_file >> $current_file
	done
done
rm $temp_file

cd $return_dir