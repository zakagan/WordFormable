#!/bin/bash
clear

path="../test_files/"
name="words"
extension=".txt"
copies=("" "2" "4" "8" "16" "32" "64" "128" "256" "512")

for val in ${copies[@]}; do
	touch $path$name$val$extension
done

cat /usr/share/dict/words > $path$name$extension

for i in $(seq 1 ${#copies[@]}); do
	cat $path$name${copies[$i-1]}$extension >> $path$name${copies[i]}$extension
	cat $path$name${copies[$i-1]}$extension >> $path$name${copies[i]}$extension
done
