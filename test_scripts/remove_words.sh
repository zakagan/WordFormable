#!/bin/bash

return_dir=`pwd`
cd "${0%/*}"

path="../test_files/words/"
name="words"
prefix=$path$name
extension=".txt"

if [ ! -d "$path" ]; then
  mkdir -p "$path"
fi

rm -rf $path

cd $return_dir
