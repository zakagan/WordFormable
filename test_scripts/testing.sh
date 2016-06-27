#!/bin/bash
clear

return_dir=`pwd`
cd "${0%/*}"

./setup_words.sh
./setup_worst_case.sh

./test_num_words.sh
./test_len_base.sh
./test_worst_case.sh
./test_load_factor.sh

./remove_words.sh
./remove_worst_case.sh

cd $return_dir 