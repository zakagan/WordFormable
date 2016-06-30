!/bin/bash
clear

return_dir=pwd
cd "${0%/*}"

path="../test_files/worst_case/"
name="worst_case"
prefix=$path$name
extension=".txt"

if [ ! -d "$path" ]; then
  mkdir -p $path
fi

for ((i=0;i<=26;i+=2)); do
	rm $prefix$i$extension
done

rm $path

cd $return_dir