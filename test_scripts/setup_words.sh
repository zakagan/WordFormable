#!/bin/bash
clear

return_dir=`pwd`
cd "${0%/*}"

path="../test_files/words/"
name="words"
prefix=$path$name
extension=".txt"

if [ ! -d "$path" ]; then
  mkdir -p $path
fi

declare -a ITERATIONS
for num in {0..9}; do 
	ITERATIONS[$num]=$((2**$num))
done

iter_val=ITERATIONS[0]
cat /usr/share/dict/words > $prefix${!iter_val}$extension

for ((i=1; i<${#ITERATIONS[@]}; i++)); do
	iter_val_prev=$iter_val
	iter_val=ITERATIONS[$i]
	for j in {1..2}; do
	cat $prefix${!iter_val_prev}$extension >> $prefix${!iter_val}$extension
	done
done

cd $return_dir