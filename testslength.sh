#! /bin/bash
clear

touch testlength.txt

echo "Basic file length results
ten char strings: 
hSF9RITZYq
OHx1ZEHiht
9cBqvgN0Qv
c0FnTkWjuL
Yl69pHrgvy

" 1>> testlength.txt

echo "WordPercentSort
" 1>> testlength.txt

echo "file 1
" 1>> testlength.txt

(/usr/bin/time ./WordPercentSort hSF9RITZYq words.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentSort OHx1ZEHiht words.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort 9cBqvgN0Qv words.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort c0FnTkWjuL words.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort Yl69pHrgvy words.txt) 2>> testlength.txt 1> /dev/null

echo "file 2
" 1>> testlength.txt

(/usr/bin/time ./WordPercentSort hSF9RITZYq words2.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentSort OHx1ZEHiht words2.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort 9cBqvgN0Qv words2.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort c0FnTkWjuL words2.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort Yl69pHrgvy words2.txt) 2>> testlength.txt 1> /dev/null


echo "file 3
" 1>> testlength.txt

(/usr/bin/time ./WordPercentSort hSF9RITZYq words4.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentSort OHx1ZEHiht words4.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort 9cBqvgN0Qv words4.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort c0FnTkWjuL words4.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort Yl69pHrgvy words4.txt) 2>> testlength.txt 1> /dev/null

echo "file 4
" 1>> testlength.txt

(/usr/bin/time ./WordPercentSort hSF9RITZYq words8.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentSort OHx1ZEHiht words8.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort 9cBqvgN0Qv words8.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort c0FnTkWjuL words8.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort Yl69pHrgvy words8.txt) 2>> testlength.txt 1> /dev/null

echo "file 5
" 1>> testlength.txt

(/usr/bin/time ./WordPercentSort hSF9RITZYq words16.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentSort OHx1ZEHiht words16.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort 9cBqvgN0Qv words16.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort c0FnTkWjuL words16.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort Yl69pHrgvy words16.txt) 2>> testlength.txt | awk 'NR==2{print $7} NR==3{print $8}' 1>> testlength.

echo "file 6
" 1>> testlength.txt

(/usr/bin/time ./WordPercentSort hSF9RITZYq words32.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentSort OHx1ZEHiht words32.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort 9cBqvgN0Qv words32.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort c0FnTkWjuL words32.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort Yl69pHrgvy words32.txt) 2>> testlength.txt 1> /dev/null

echo "file 7
" 1>> testlength.txt

(/usr/bin/time ./WordPercentSort hSF9RITZYq words64.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentSort OHx1ZEHiht words64.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort 9cBqvgN0Qv words64.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort c0FnTkWjuL words64.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort Yl69pHrgvy words64.txt) 2>> testlength.txt | awk 'NR==2{print $7} NR==3{print $8}' 1>> testlength.

echo "file 8
" 1>> testlength.txt

(/usr/bin/time ./WordPercentSort hSF9RITZYq words128.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentSort OHx1ZEHiht words128.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort 9cBqvgN0Qv words128.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort c0FnTkWjuL words128.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort Yl69pHrgvy words128.txt) 2>> testlength.txt 1> /dev/null


echo "file 9
" 1>> testlength.txt

(/usr/bin/time ./WordPercentSort hSF9RITZYq words256.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentSort OHx1ZEHiht words256.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort 9cBqvgN0Qv words256.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort c0FnTkWjuL words256.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort Yl69pHrgvy words256.txt) 2>> testlength.txt 1> /dev/null

echo "file 10
" 1>> testlength.txt

(/usr/bin/time ./WordPercentSort hSF9RITZYq words512.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentSort OHx1ZEHiht words512.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort 9cBqvgN0Qv words512.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort c0FnTkWjuL words512.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentSort Yl69pHrgvy words512.txt) 2>> testlength.txt 1> /dev/null

echo "WordPercentTable
" 1>> testlength.txt

echo "file 1
" 1>> testlength.txt

(/usr/bin/time ./WordPercentTable hSF9RITZYq words.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentTable OHx1ZEHiht words.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable 9cBqvgN0Qv words.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable c0FnTkWjuL words.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable Yl69pHrgvy words.txt) 2>> testlength.txt 1> /dev/null

echo "file 2
" 1>> testlength.txt

(/usr/bin/time ./WordPercentTable hSF9RITZYq words2.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentTable OHx1ZEHiht words2.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable 9cBqvgN0Qv words2.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable c0FnTkWjuL words2.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable Yl69pHrgvy words2.txt) 2>> testlength.txt 1> /dev/null


echo "file 3
" 1>> testlength.txt

(/usr/bin/time ./WordPercentTable hSF9RITZYq words4.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentTable OHx1ZEHiht words4.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable 9cBqvgN0Qv words4.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable c0FnTkWjuL words4.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable Yl69pHrgvy words4.txt) 2>> testlength.txt 1> /dev/null

echo "file 4
" 1>> testlength.txt

(/usr/bin/time ./WordPercentTable hSF9RITZYq words8.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentTable OHx1ZEHiht words8.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable 9cBqvgN0Qv words8.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable c0FnTkWjuL words8.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable Yl69pHrgvy words8.txt) 2>> testlength.txt 1> /dev/null

echo "file 5
" 1>> testlength.txt

(/usr/bin/time ./WordPercentTable hSF9RITZYq words16.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentTable OHx1ZEHiht words16.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable 9cBqvgN0Qv words16.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable c0FnTkWjuL words16.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable Yl69pHrgvy words16.txt) 2>> testlength.txt 1> /dev/null

echo "file 6
" 1>> testlength.txt

(/usr/bin/time ./WordPercentTable hSF9RITZYq words32.txt)  >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentTable OHx1ZEHiht words32.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable 9cBqvgN0Qv words32.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable c0FnTkWjuL words32.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable Yl69pHrgvy words32.txt) 2>> testlength.txt 1> /dev/null

echo "file 7
" 1>> testlength.txt

(/usr/bin/time ./WordPercentTable hSF9RITZYq words64.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentTable OHx1ZEHiht words64.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable 9cBqvgN0Qv words64.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable c0FnTkWjuL words64.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable Yl69pHrgvy words64.txt) 2>> testlength.txt 1> /dev/null

echo "file 8
" 1>> testlength.txt

(/usr/bin/time ./WordPercentTable hSF9RITZYq words128.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentTable OHx1ZEHiht words128.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable 9cBqvgN0Qv words128.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable c0FnTkWjuL words128.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable Yl69pHrgvy words128.txt) 2>> testlength.txt 1> /dev/null


echo "file 9
" 1>> testlength.txt

(/usr/bin/time ./WordPercentTable hSF9RITZYq words256.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentTable OHx1ZEHiht words256.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable 9cBqvgN0Qv words256.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable c0FnTkWjuL words256.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable Yl69pHrgvy words256.txt) 2>> testlength.txt 1> /dev/null

echo "file 10
" 1>> testlength.txt

(/usr/bin/time ./WordPercentTable hSF9RITZYq words512.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentTable OHx1ZEHiht words512.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable 9cBqvgN0Qv words512.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable c0FnTkWjuL words512.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentTable Yl69pHrgvy words512.txt) 2>> testlength.txt 1> /dev/null

echo "WordPercentPrecomputeSort
" 1>> testlength.txt

echo "file 1
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeSort hSF9RITZYq words.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeSort OHx1ZEHiht words.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort 9cBqvgN0Qv words.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort c0FnTkWjuL words.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort Yl69pHrgvy words.txt) 2>> testlength.txt 1> /dev/null

echo "file 2
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeSort hSF9RITZYq words2.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeSort OHx1ZEHiht words2.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort 9cBqvgN0Qv words2.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort c0FnTkWjuL words2.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort Yl69pHrgvy words2.txt) 2>> testlength.txt 1> /dev/null


echo "file 3
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeSort hSF9RITZYq words4.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeSort OHx1ZEHiht words4.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort 9cBqvgN0Qv words4.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort c0FnTkWjuL words4.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort Yl69pHrgvy words4.txt) 2>> testlength.txt 1> /dev/null

echo "file 4
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeSort hSF9RITZYq words8.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeSort OHx1ZEHiht words8.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort 9cBqvgN0Qv words8.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort c0FnTkWjuL words8.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort Yl69pHrgvy words8.txt) 2>> testlength.txt 1> /dev/null

echo "file 5
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeSort hSF9RITZYq words16.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeSort OHx1ZEHiht words16.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort 9cBqvgN0Qv words16.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort c0FnTkWjuL words16.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort Yl69pHrgvy words16.txt) 2>> testlength.txt | awk 'NR==2{print $7} NR==3{print $8}' 1>> testlength.

echo "file 6
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeSort hSF9RITZYq words32.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeSort OHx1ZEHiht words32.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort 9cBqvgN0Qv words32.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort c0FnTkWjuL words32.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort Yl69pHrgvy words32.txt) 2>> testlength.txt 1> /dev/null

echo "file 7
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeSort hSF9RITZYq words64.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeSort OHx1ZEHiht words64.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort 9cBqvgN0Qv words64.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort c0FnTkWjuL words64.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort Yl69pHrgvy words64.txt) 2>> testlength.txt | awk 'NR==2{print $7} NR==3{print $8}' 1>> testlength.

echo "file 8
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeSort hSF9RITZYq words128.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeSort OHx1ZEHiht words128.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort 9cBqvgN0Qv words128.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort c0FnTkWjuL words128.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort Yl69pHrgvy words128.txt) 2>> testlength.txt 1> /dev/null


echo "file 9
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeSort hSF9RITZYq words256.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeSort OHx1ZEHiht words256.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort 9cBqvgN0Qv words256.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort c0FnTkWjuL words256.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort Yl69pHrgvy words256.txt) 2>> testlength.txt 1> /dev/null

echo "file 10
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeSort hSF9RITZYq words512.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeSort OHx1ZEHiht words512.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort 9cBqvgN0Qv words512.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort c0FnTkWjuL words512.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeSort Yl69pHrgvy words512.txt) 2>> testlength.txt 1> /dev/null

echo "WordPercentPrecomputeTable
" 1>> testlength.txt

echo "file 1
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeTable hSF9RITZYq words.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeTable OHx1ZEHiht words.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable 9cBqvgN0Qv words.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable c0FnTkWjuL words.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable Yl69pHrgvy words.txt) 2>> testlength.txt 1> /dev/null

echo "file 2
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeTable hSF9RITZYq words2.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeTable OHx1ZEHiht words2.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable 9cBqvgN0Qv words2.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable c0FnTkWjuL words2.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable Yl69pHrgvy words2.txt) 2>> testlength.txt 1> /dev/null


echo "file 3
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeTable hSF9RITZYq words4.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeTable OHx1ZEHiht words4.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable 9cBqvgN0Qv words4.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable c0FnTkWjuL words4.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable Yl69pHrgvy words4.txt) 2>> testlength.txt 1> /dev/null

echo "file 4
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeTable hSF9RITZYq words8.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeTable OHx1ZEHiht words8.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable 9cBqvgN0Qv words8.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable c0FnTkWjuL words8.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable Yl69pHrgvy words8.txt) 2>> testlength.txt 1> /dev/null

echo "file 5
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeTable hSF9RITZYq words16.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeTable OHx1ZEHiht words16.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable 9cBqvgN0Qv words16.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable c0FnTkWjuL words16.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable Yl69pHrgvy words16.txt) 2>> testlength.txt 1> /dev/null

echo "file 6
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeTable hSF9RITZYq words32.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeTable OHx1ZEHiht words32.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable 9cBqvgN0Qv words32.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable c0FnTkWjuL words32.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable Yl69pHrgvy words32.txt) 2>> testlength.txt 1> /dev/null

echo "file 7
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeTable hSF9RITZYq words64.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeTable OHx1ZEHiht words64.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable 9cBqvgN0Qv words64.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable c0FnTkWjuL words64.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable Yl69pHrgvy words64.txt) 2>> testlength.txt 1> /dev/null

echo "file 8
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeTable hSF9RITZYq words128.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeTable OHx1ZEHiht words128.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable 9cBqvgN0Qv words128.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable c0FnTkWjuL words128.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable Yl69pHrgvy words128.txt) 2>> testlength.txt 1> /dev/null


echo "file 9
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeTable hSF9RITZYq words256.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeTable OHx1ZEHiht words256.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable 9cBqvgN0Qv words256.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable c0FnTkWjuL words256.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable Yl69pHrgvy words256.txt) 2>> testlength.txt 1> /dev/null

echo "file 10
" 1>> testlength.txt

(/usr/bin/time ./WordPercentPrecomputeTable hSF9RITZYq words512.txt) >> testlength.txt 2>&1
(/usr/bin/time ./WordPercentPrecomputeTable OHx1ZEHiht words512.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable 9cBqvgN0Qv words512.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable c0FnTkWjuL words512.txt) 2>> testlength.txt 1> /dev/null
(/usr/bin/time ./WordPercentPrecomputeTable Yl69pHrgvy words512.txt) 2>> testlength.txt 1> /dev/null



#cut -d ':' -f2 temp.txt #1> testresults.txt

#(time ./WordPercentSort bananas words.txt) 2>> testresults.txt 1> /dev/null
