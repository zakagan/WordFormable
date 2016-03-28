WordPercent
=============

The goal of this reposititory is to solve a typical programming challenge question in as many ways as possible. Doing so is a great tool for learning how to effectively use different data structures in C. 

The challenge: Given a text file, determine the percent of words contained within that are formable from a user-inputted base string. A word is not formable unless all necessary characters are present within the base string. This includes the frequency of a given character. For example, "Mississippi" is not formable if there is only one "s" character in the base string. At least four seperate "s" chars must be present, along with all of the rest of the required letters, to form that word.

Currently two different solutions are included:

1. Sorting: The base string and tokenized words from the text file are alphabetizd via quick sort and then compared.

2. Simple Hash Table: Th base string is loaded into a table using a trivial hashing method, and then each tokenized word from the text file is compared with this table.

How to execute
-------

The program operates on the command line. A typical way to execute it would be to type:
`./WordPercent___ S  F`

Where S and F are the base string and the path to the given textfile, respectively. Replace the underline characters with ending of one of the two produced executables (each representing one solution method):

1. WordPercentSort
2. WordPercentTable

Then, printed to the command line, will be the percentage of formable words in F.

For example, you use the example text file provided and enter:

`./WordPercent____ hellomaybetext /Users/.../example.txt`

The result should be:

`Number of tokenized words read from file: 7`

`Number of words formable from the base string: 3`

`Percent of formable words: 42.86`

Assumptions
-------

I considered the following characters to be my tokenizers `\n ,.!?()<>{}[]\/`

Note that the first char is a new line, and the second is a space. End of file is also considered.

There is no maxmimum word size within the given textfile. The program dynamically allocates memory according to the length of the base string.

WordPercentSort's Implementation
-------

Basic algorithm:

1. First the text file is opened, and its contents are parsed into tokenized words.

2. When a new token is found a word counter is incremented and it gets sorted by each character's alphanumeric value using quick sort.

3. Since the token is sorted, duplicate characters are grouped together. These repeated characters are gathered into another string called partial (since it is a substrig of the sorted token). 

4. The base string is also sorted. If the partial string is not a substring of the sorted base string, then the required letters to form the token must not exist within the base string. If this occurs the program moves to the next token.

5. If all partial strings (representing each set of unique characters in the token) exist in the base string, a formed word counter is incremented.

6. The percentage of formed words is calculated based on the two counters, and returned via the command line. The file is then closed.

A Third Solution
-------

Another solution to this problem has been considered, but not yet included: precomputing all possible formable words from th base string. This would be effcient given a sort base string and a long text file with many words. 

However, the challenge with this method is both computing the power set of the base string and choosing an effcient hash function. Currently this is a work in progress,

