#!/bin/bash
clear

return_dir=`pwd`
cd "${0%/*}"

input_path="../test_files/words/"
input_name="words128"
extension=".txt"
input_file=$input_path$input_name$extension

results_path="../test_results/"
results_name="results_len_base"
results_file=$results_path$results_name$extension

executable_path="../"

if [ ! -d "$result_path" ]; then
  mkdir $result_path
fi

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

echo "Testing K: base string length"  1> $results_file
echo "" 1>> $results_file

for ((i=0;i<=26;i+=2)); do
	array_var=base_str_$i[*]
	for string in ${!array_var}; do
		echo $string 1>> $results_file
	done	
done

for executable in WordPercentSort WordPercentTable WordPercentPrecomputeSort WordPercentPrecomputeTable; do

	echo "" 1>> $results_file
	echo "SOLUTION: $executable" 1>> $results_file

	for ((i=0;i<=26;i+=2)); do

		echo "" 1>> $results_file
		echo "FILE: $input_file" 1>> $results_file
		echo "LENGTH: $i" 1>> $results_file
		array_var=base_str_$i[0]
		echo "$executable_path$executable ${!array_var} $input_file" 1>> $results_file
		(time $executable_path$executable ${!array_var} $input_file) >> $results_file 2>&1
		for ((j=1;j<=4;j++)); do
			array_var=base_str_$i[$j]
			(time $executable_path$executable ${!array_var} $input_file) 2>> $results_file 1> /dev/null
		done
	done
done

cd $return_dir 