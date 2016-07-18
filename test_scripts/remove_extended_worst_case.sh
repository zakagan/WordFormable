#!/bin/bash

return_dir=pwd
cd "${0%/*}"

path="../test_files/worst_case/"
name="worst_case"
prefix=$path$name
extension=".txt"

if [ ! -d "$path" ]; then
  mkdir -p "$path"
fi

EWC_STR_LEN=()
for ((i=25;i<=60;i+=5)); do 
	WC_STR_LEN+=($i)
done

for len in ${EWC_STR_LEN[@]}; do
	rm $prefix$len$extension
done

rm -r $path

cd $return_dir