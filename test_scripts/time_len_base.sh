#!/bin/bash

return_dir=`pwd`
cd "${0%/*}"

time_stamp=`date +%Y-%m-%d__%H_%M_%S`

extension=".txt"

input_path="../test_files/words/"
input_name="words512"
input_file=$input_path$input_name$extension

results_path="../test_results/"
mkdir -p $results_path
results_path="${results_path}len_base_"
results_prefix="results_LB_"
results_suffix="_${time_stamp}${extension}"

executable_path="../"
executables=("WordFormablePartials" "WordFormableTable" "WordFormablePowerPC" "WordFormablePowerHP")

base_str_0=("\"\"" "\"\"" "\"\"" "\"\"" "\"\"")
base_str_2=("so" "vq" "us" "ih" "jg")
base_str_4=("srks" "aysr" "qevz" "qmrz" "ltat")
base_str_6=("tbualw" "tfcuiy" "niulid" "nhkzwd" "zfjqfq")
base_str_8=("wrqisywh" "rtodltey" "flcvttwk" "nizfydpv" "yqimsitd")
base_str_10=("qavjgstsme" "zryyoubwmt" "tcmdurgcsu" "zyxuapvoma" "gvdrmkbtpu")
base_str_12=("jpolfemolira" "nwqakjgytvxc" "vjbmtlgfmutx" "nksckwdrriml" "kvbbkqhsabmp")
base_str_14=("xywpdsfvnlkcja" "npievppnzctzoa" "zojqahqkmlsygq" "yhqdsfftmyvuir" "cstyzmniqepoug")
base_str_16=("zudjxyrwtbnjoant" "xmoqxoraqqihccgc" "hadrpuvlfniwnckb" "przqkphiiyvklklu" "qbszcpiceaeablmu")
base_str_18=("bmwctyrkehpzyucuuf" "zuioxcygravhwqvaal" "wimprbnjkyzuscyaow" "pdgneasxulyfltscln" "oobrqggznllqyczyeg")
base_str_20=("fvjkvublsoyixuorvfpw" "gcgjgfytgmrjcraheuvk" "cyuefubukwbcsraxhelr" "odbstqkwebhbojdjiefs" "pfffbmkjdwuhxqatchqt")
base_str_22=("gerxfcxdezbhkjmvbmgmjq" "zvhelqfuhmjwrulgjvvkus" "aqthcbknvdilwxdgutukiz" "euudbfiollxyzhnzocnqqm" "uzpsuhdbarijlrjhguyipa")
base_str_24=("kmhvgqccdffynnwfhifsyjlg" "tfyefzrisxbpqqgribcwnhgk" "mepxbxdmjsakenbxszxmrvnb" "ufphaijcyipfgsjsgydmjbbm" "bljrrchtpouzbvwvcabirtnt")
base_str_26=("gsfephucisjfizooxktpqmujln" "kkujxjknhojavymrxjchrdsowh" "biakzjkivxktxwdrjvuxpyqwvs" "dhppsrooxthlhammdfkhqvtnaz" "liyrrvydsdgarskrvvbnucnqqj")

BASE_STR_LEN=()
for ((i=0;i<=26;i+=2)); do 
	BASE_STR_LEN+=($i)
done

n=0
results_path_attempt="${results_path}${n}/"
while ! mkdir "$results_path_attempt" 2> /dev/null; do
	n=$((n+1))
	results_path_attempt="${results_path}${n}/"
done
results_path=$results_path_attempt

#Header
for executable in ${executables[@]}; do
	results_file=$results_path$results_prefix$executable$results_suffix
	echo "Testing K: base string length"  1> $results_file
	echo "SOLUTION: $executable" 1>> $results_file
	echo "FILE: $input_file" 1>> $results_file
	echo ""  1>> $results_file
	for len in ${BASE_STR_LEN[@]}; do
		array_var=base_str_${len}[*]
		for string in ${!array_var}; do
			echo $string 1>> $results_file
		done	
	done
done

#Tests
for len in ${BASE_STR_LEN[@]}; do
	for executable in ${executables[@]}; do
		results_file=$results_path$results_prefix$executable$results_suffix
		array_var=base_str_$len[0]
		echo "" 1>> $results_file
		echo "LENGTH: $len" 1>> $results_file
		echo "$executable_path$executable ${!array_var} $input_file 1" 1>> $results_file
		(time $executable_path$executable ${!array_var} $input_file 1) >> $results_file 2>&1
		for ((j=1;j<=4;j++)); do
			array_var=base_str_$len[$j]
			(time $executable_path$executable ${!array_var} $input_file 1) 2>> $results_file 1> /dev/null
		done
	done
done

cd $return_dir 

### What a slow computation
### real	40m31.513s
### user	40m31.949s
### sys	0m0.336s