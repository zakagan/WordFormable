#!/bin/bash
clear

return_dir=`pwd`
cd "${0%/*}"

path="../test_files/worst_case/"
name="worst_case"
extension=".txt"
prefix=$path$name

if [ ! -d "$path" ]; then
  mkdir -p "$path"
fi

worst_case_array[0]="\"\""
worst_case_array[2]="ov"
worst_case_array[4]="agD3"
worst_case_array[6]="wgqJa2"
worst_case_array[8]="Ky7tJ46c"
worst_case_array[10]="EMCQdZ3klS"
worst_case_array[12]="4ClbGRUzEskb"
worst_case_array[14]="A1GYMKYgDBcabv"
worst_case_array[16]="0oEBDmSijxKcOLUR"
worst_case_array[18]="5N6cUHil5gSwpvquYL"
worst_case_array[20]="9VWyrpuWvgLzE5v7Tu0t"
worst_case_array[22]="QdjnttnvPq6CwtorpdqnZl"
worst_case_array[24]="AucL8asugf8sNOTGZ5YyrZ6v"
worst_case_array[26]="GI8KPcXVL5lPcxoxVUoeg0PZK7"

temp_name="temp"
temp_file=$path$temp_name$extension
for ((i=0;i<=26;i+=2)); do
	current_file=$prefix$i$extension
	echo ${worst_case_array[$i]} > $current_file
	for ((j=0;j<26;j++)); do
		cat $current_file > $temp_file
		cat $temp_file >> $current_file
	done
done
rm $temp_file

cd $return_dir