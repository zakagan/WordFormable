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
./setup_worst_case.sh 0
####TEST SCRIPTS FOR INITIAL WORST CASE SCENARIO####
echo "Timing solutions over length of base string in the initial worst case scenario."
./time_worst_case.sh 0
####DELETES INITIAL WORST CASE TESTING FILES####
echo "Removing initial worst case files."
./remove_worst_case.sh

####GENERATES 2nd WORST CASE TESTING FILES####
echo "Generating initial worst case test files."
./setup_worst_case.sh 1
####TEST SCRIPTS FOR 2nd WORST CASE SCENARIO####
echo "Timing solutions over length of base string in the initial worst case scenario."
./time_worst_case.sh 1
####DELETES 2nd WORST CASE TESTING FILES####
echo "Removing initial worst case files."
./remove_worst_case.sh

####GENERATES 3rd WORST CASE TESTING FILES####
echo "Generating initial worst case test files."
./setup_worst_case.sh 2
####TEST SCRIPTS FOR 3rd WORST CASE SCENARIO####
echo "Timing solutions over length of base string in the initial worst case scenario."
./time_worst_case.sh 2
####DELETES 2nd WORST CASE TESTING FILES####
echo "Removing initial worst case files."
./remove_worst_case.sh

####GENERATES 4th WORST CASE TESTING FILES####
echo "Generating initial worst case test files."
./setup_worst_case.sh 3
####TEST SCRIPTS FOR 3rd WORST CASE SCENARIO####
echo "Timing solutions over length of base string in the initial worst case scenario."
./time_worst_case.sh 3
####DELETES 2nd WORST CASE TESTING FILES####
echo "Removing initial worst case files."
./remove_worst_case.sh

echo "Testing sequence completed."

cd $return_dir 