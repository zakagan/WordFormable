!/bin/bash
clear

return_dir=pwd
cd "${0%/*}"

path="../test_files/"
name="worst_case"
prefix=$path$name
extension=".txt"

for ((i=0;i<=26;i+=2)); do
	rm $prefix$i$extension
done

cd $return_dir