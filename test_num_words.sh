#! /bin/bash
clear

file_name="results_num_words.txt"

touch $file_name

echo "Testing N: file length by word count
ten char strings: 
hSF9RITZYq
OHx1ZEHiht
9cBqvgN0Qv
c0FnTkWjuL
Yl69pHrgvy
"  1> $file_name

for executable in ./WordPercentSort ./WordPercentTable ./WordPercentPrecomputeSort ./WordPercentPrecomputeTable; do

	echo "
	$executable" 1>> $file_name

	for i in "" "2" "4" "8" "16" "32" "64" "128" "256" "512"; do

		echo "
		file: words$i
		" 1>> $file_name

		(time ./WordPercentSort hSF9RITZYq words$i.txt) >> $file_name 2>&1
		(time ./WordPercentSort OHx1ZEHiht words$i.txt) 2>> $file_name 1> /dev/null
		(time ./WordPercentSort 9cBqvgN0Qv words$i.txt) 2>> $file_name 1> /dev/null
		(time ./WordPercentSort c0FnTkWjuL words$i.txt) 2>> $file_name 1> /dev/null
		(time ./WordPercentSort Yl69pHrgvy words$i.txt) 2>> $file_name 1> /dev/null

	done

done

