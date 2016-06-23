#!/bin/bash
clear

return_dir=pwd
cd "${0%/*}"

path="../test_files/"
name="words"
extension=".txt"
copies=("" "2" "4" "8" "16" "32" "64" "128" "256" "512")

cat /usr/share/dict/words > $path$name$extension

for ((i=1;i<${#copies[@]};i++)); do
	cat $path$name${copies[$i-1]}$extension >> $path$name${copies[i]}$extension
	cat $path$name${copies[$i-1]}$extension >> $path$name${copies[i]}$extension
done

cd return_dir