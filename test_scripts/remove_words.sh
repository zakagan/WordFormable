#!/bin/bash
clear

return_dir=pwd
cd "${0%/*}"

path="../test_files/"
name="words"
extension=".txt"
copies=("" "2" "4" "8" "16" "32" "64" "128" "256" "512")

for ((i=0;i<${#copies[@]};i++)); do
	rm $path$name${copies[i]}$extension
done

cd return_dir
