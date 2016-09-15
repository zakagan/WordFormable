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

test_str="zyxwvutsrqponmlkjihgfedcba9876543210ZYXWVUTSRQPONMLKJIHGFEDCBA"  		#62 chars long
padding_str=".............................................................."	#also 62 chars

temp_name="temp"
temp_file=$path$temp_name$extension

WC_STR_LEN=()

case $1 in
	0)
		for ((i=0;i<=11;++i)); do 
			WC_STR_LEN+=($i)
		done
		;;
	1)
		for ((i=12;i<=23;++i)); do 
			WC_STR_LEN+=($i)
		done
		;;
	2)
		for ((i=24;i<=35;++i)); do 
			WC_STR_LEN+=($i)
		done
		;;
	3)
		for ((i=36;i<=58;i+=2)); do 
			WC_STR_LEN+=($i)
		done
		WC_STR_LEN+=(61)
		;;
	*)
		echo "Use an integer input (0, 1, 2, or 3) to select which set of worst case test files to generate"
		;;
esac

for len in ${WC_STR_LEN[@]}; do
	pad_len=$(((62-len)/2))
	current_file=$prefix$len$extension
	if [ $((len%2)) -eq 0 ]; then
		current_str=${padding_str:0:$pad_len}${test_str:0:$len}${padding_str:0:$pad_len}
	else 
		current_str=${padding_str:0:$pad_len}${test_str:0:$len}${padding_str:0:$((pad_len+1))} 
	fi

	echo $current_str > $current_file
	for ((j=0;j<=22;j++)); do
		cat $current_file > $temp_file
		cat $temp_file >> $current_file
	done
done
rm $temp_file

cd $return_dir