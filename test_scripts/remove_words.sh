#!/bin/bash

return_dir=`pwd`
cd "${0%/*}"

path="../test_files/words/"
name="words"
prefix=$path$name
extension=".txt"

if [ ! -d "$path" ]; then
  mkdir -p "$path"
fi

declare -a ITERATIONS
for num in {0..9}; do 
	ITERATIONS[$num]=$((2**$num))
done

for ((i=0;i<${#ITERATIONS[@]};i++)); do
	rm $prefix${ITERATIONS[i]}$extension
done

rm -r $path

cd $return_dir
