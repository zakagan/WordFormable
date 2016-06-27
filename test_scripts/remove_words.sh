#!/bin/bash
clear

return_dir=`pwd`
cd "${0%/*}"

path="../test_files/"
name="words"
predix=$path$name
extension=".txt"

declare -a ITERATIONS
for num in {0..9}; do 
	ITERATIONS[$num]=$((2**$num))
done


for ((i=0;i<${#ITERATIONS[@]};i++)); do
	rm $path$name${ITERATIONS[i]}$extension
done

cd $return_dir
