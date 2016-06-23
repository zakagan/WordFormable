!/bin/bash
clear

return_dir=pwd
cd "${0%/*}"

path="../test_files/"
name="worst_case"
extension=".txt"

for ((i=0;i<=26;i+=2)); do
	rm $path$name$i$extension
done

cd return_dir