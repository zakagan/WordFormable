#!/bin/bash

return_dir=`pwd`
cd "${0%/*}"

path="../test_files/worst_case/"
name="worst_case"
prefix=$path$name
extension=".txt"

if [ ! -d "$path" ]; then
  mkdir -p "$path"
fi

WC_STR_LEN=()
if [ "${1:0:1}" = "e" ] || [ "${1:0:1}" = "E" ]; then
	# range of string lengths for the extended worst case scenario
	for ((i=30;i<=63;i+=6)); do 
		WC_STR_LEN+=($i)
	done
	WC_STR_LEN+=(63)
elif [ "${1:0:1}" = "i" ] || [ "${1:0:1}" = "I" ]; then
	# range of string lengths for the intermediate worst case scenario
	for ((i=25;i<=29;i+=1)); do 
		WC_STR_LEN+=($i)
	done
	WC_STR_LEN+=(32)
	WC_STR_LEN+=(34)
else
	# range of string lengths for the intial worst case scenario
	for ((i=0;i<=24;i+=1)); do 
		WC_STR_LEN+=($i)
	done
fi

for len in ${WC_STR_LEN[@]}; do
	rm $prefix$len$extension
done

rm -r $path

cd $return_dir