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
if [ "${1:0:1}" != "e" ] && [ "${1:0:1}" != "E" ]; then
	for ((i=0;i<=24;i+=1)); do 
		WC_STR_LEN+=($i)
	done
else
	for ((i=29;i<=63;i+=5)); do 
		WC_STR_LEN+=($i)
	done
	WC_STR_LEN+=(63)
fi

for len in ${WC_STR_LEN[@]}; do
	rm $prefix$len$extension
done

rm -r $path

cd $return_dir