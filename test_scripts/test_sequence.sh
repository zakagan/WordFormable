#!/bin/bash
clear

return_dir=`pwd`
cd "${0%/*}"

echo "Starting testing sequence, this will take several minutes."

####GENERATES GENERAL/AVERAGE CASE TESTING FILES####
echo "Generating average case test files."
./setup_words.sh

####TEST SCRIPTS USING WORDS TEXT FILES####
echo "Timing solutions over number of words per file."
./time_num_words.sh
echo "Timing solutions over length of base string."
./time_len_base.sh
echo "Timing hash map solutions over various load factors."
./time_load_factor.sh

####DELETES GENERAL/AVERAGE CASE TESTING FILES####
echo "Removing average case files."
./remove_words.sh

####GENERATES WORST CASE TESTING FILES####
echo "Generating worst case test files."
./setup_worst_case.sh
####TEST SCRIPTS FOR WORST CASE SCENARIO####
echo "Timing solutions over length of base string in the worst case scenario."
./time_worst_case.sh
####DELETES WORST CASE TESTING FILES####
echo "Removing worst case files."
./remove_worst_case.sh

echo "Testing sequence completed."

cd $return_dir 