#!/bin/bash
clear

path="../test_results/"
file_name="results_len_base.txt"
touch $file_name

base_str_0=("" "" "" "" "")
base_str_2=("so" "vq" "us" "ih" "jg")
base_str_5=("srksu" "aysrw" "qevzn" "qmrzy" "ltatp")
base_str_8=("wrqisywh" "rtodltey" "flcvttwk" "nizfydpv" "yqimsitd")
base_str_10=("qavjgstsme" "zryyoubwmt" "tcmdurgcsu" "zyxuapvoma" "gvdrmkbtpu")
base_str_12=("jpolfemolira" "nwqakjgytvxc" "vjbmtlgfmutx" "nksckwdrriml" "kvbbkqhsabmp")
base_str_15=("xywpdsfvnlkcjay" "npievppnzctzoaj" "zojqahqkmlsygqa" "yhqdsfftmyvuirn" "cstyzmniqepougr")
base_str_18=("bmwctyrkehpzyucuuf" "zuioxcygravhwqvaal" "wimprbnjkyzuscyaow" "pdgneasxulyfltscln" "oobrqggznllqyczyeg")
base_str_20=("fvjkvublsoyixuorvfpw" "gcgjgfytgmrjcraheuvk" "cyuefubukwbcsraxhelr" "odbstqkwebhbojdjiefs" "pfffbmkjdwuhxqatchqt")
base_str_22=("gerxfcxdezbhkjmvbmgmjq" "zvhelqfuhmjwrulgjvvkus" "aqthcbknvdilwxdgutukiz" "euudbfiollxyzhnzocnqqm" "uzpsuhdbarijlrjhguyipa")
base_str_24=("kmhvgqccdffynnwfhifsyjlg" "tfyefzrisxbpqqgribcwnhgk" "mepxbxdmjsakenbxszxmrvnb" "ufphaijcyipfgsjsgydmjbbm" "bljrrchtpouzbvwvcabirtnt")

echo "Testing K: base string length"  1> $path$file_name
echo "" 1>> $path$file_name

for i in  "0" "2" "5" "8" "10" "12" "15" "18" "20" "22" "24"; do
	array_var=base_str_$i[*]
	for string in ${!array_var}; do
		echo $string 1>> $path$file_name
	done	
done

for executable in ./WordPercentSort ./WordPercentTable ./WordPercentPrecomputeSort ./WordPercentPrecomputeTable; do

	echo "" 1>> $path$file_name
	echo "$executable" 1>> $path$file_name

	for i in  "0" "2" "5" "8" "10" "12" "15" "18" "20" "22" "24"; do

		echo "" 1>> $path$file_name
		echo "base string length: $i" 1>> $path$file_name
		echo "" 1>> $path$file_name
		array_var=base_str_$i[0]
		(time $executable ${!array_var} words512.txt) >> $path$file_name 2>&1
		for j in {1..4}; do
			array_var=base_str_$i[$j]
			(time $executable ${!array_var} words512.txt) 2>> $path$file_name 1> /dev/null
		done
	done
done