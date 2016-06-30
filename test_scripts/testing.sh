#!/bin/bash
clear

return_dir=`pwd`
cd "${0%/*}"

####GENERATES GENERAL/AVERAGE CASE TESTING FILES####
./setup_words.sh

####TEST SCRIPTS USING WORDS TEXT FILES####
./test_num_words.sh
./test_len_base.sh
./test_load_factor.sh

####DELETES GENERAL/AVERAGE CASE TESTING FILES####
./remove_words.sh

####GENERATES WORST CASE TESTING FILES####
./setup_worst_case.sh
####TEST SCRIPTS FOR WORST CASE SCENARIO####
./test_worst_case.sh
####DELETES WORST CASE TESTING FILES####
./remove_worst_case.sh

cd $return_dir 