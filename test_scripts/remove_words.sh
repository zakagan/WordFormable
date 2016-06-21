#!/bin/bash
clear

path="../test_files/"
name="words"
extension=".txt"
copies=("" "2" "4" "8" "16" "32" "64" "128" "256" "512")

for val in ${copies[@]}; do
	touch $path$name$val$extension
done

for i in $(seq 0 $((${#copies[@]}-1))); do
	rm $path$name${copies[i]}$extension
done
