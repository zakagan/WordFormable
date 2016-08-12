#!/bin/bash
clear

return_dir=`pwd`
cd "${0%/*}"

echo "Starting testing sequence, this will take a few hours..."

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

####GENERATES INITIAL WORST CASE TESTING FILES####
echo "Generating initial worst case test files."
./setup_worst_case.sh
####TEST SCRIPTS FOR INITIAL WORST CASE SCENARIO####
echo "Timing solutions over length of base string in the initial worst case scenario."
./time_worst_case.sh
####DELETES INITIAL WORST CASE TESTING FILES####
echo "Removing initial worst case files."
./remove_worst_case.sh

####GENERATES EXTENDED WORST CASE TESTING FILES####
echo "Generating extended worst case test files."
./setup_worst_case.sh e
####TEST SCRIPTS FOR EXTENDED WORST CASE SCENARIO####
echo "Timing solutions over length of base string in the extended worst case scenario."
./time_worst_case.sh e
####DELETES EXTENDED WORST CASE TESTING FILES####
echo "Removing extended worst case files."
./remove_worst_case.sh e


echo "Testing sequence completed."

cd $return_dir 