WordPercent
=============

The goal of this reposititory is to solve a typical programming challenge question in as many ways as possible. Doing so is a great tool for learning how to effectively use different data structures in C. 

The Challenge
-------

Given a text file, determine the percent of words contained within that are formable from a user-inputted base string. Strings are case sensitive. A word is not formable unless all necessary characters are present within the base string.

This includes the frequency of a given character. For example, "Mississippi" is not formable if there is only one "s" character in the base string. At least four seperate "s" chars must be present, along with all of the rest of the required letters, to form that word.

Currently two different solutions are included:

1. Sorting: The base string and tokenized words from the text file are alphabetizd via quick sort and then compared.

2. Simple Hash Table: The base string is loaded into a table using a trivial hashing method, and then each tokenized word from the text file is compared with this table.

How to execute
-------

First compile the executables using the provided Makefile.

The program operates on the command line. A typical way to execute it would be to type:
`./WordPercent___ S  F`

Where S and F are the base string and the path to the given textfile, respectively. Replace the underline characters with ending of one of the two produced executables (each representing one solution method):

1. WordPercentSort
2. WordPercentTable

Then, printed to the command line, will be the percentage of formable words in F.

For example, you use the example text file provided and enter:

`./WordPercentTable helloworld /Users/.../example.txt`

The result should be:

```bash
Number of tokenized words read from file: 7
Number of words formable from the base string: 3
Percent of formable words: 42.86
```

Assumptions
-------

I considered the following characters to be my tokenizers `\n ,.!?()<>{}[]\/`

Note that the first char is a new line, and the second is a space. End of file is also considered.

There is no maxmimum word size within the given textfile. The program dynamically allocates memory according to the length of the base string.

WordPercentSort's Implementation and Complexity
-------

Basic algorithm:

1. First the text file is opened, and its contents are parsed into tokenized words.

2. When a new token is found a word counter is incremented and it gets sorted by each character's alphanumeric value using quick sort.

3. Since the token is sorted, duplicate characters are grouped together. These repeated characters are gathered into another string called partial (since it is a substring of the sorted token). 

4. The base string is also sorted. If the partial string is not a substring of the sorted base string, then the required letters to form the token must not exist within the base string. If this occurs the program moves to the next token.

5. If all partial strings (representing each set of unique characters in the token) exist in the base string, a formed word counter is incremented.

6. The percentage of formed words is calculated based on the two counters, and returned via the command line. The file is then closed.

What about the computational complexity of the sorting solution? Let there be N words in the textfile, each word with average length M. This solution needs to sort all N words using quick sort, so its complexity is O(NMlog(M)).

WordPercentTable's Implementation and Complexity
-------

Basic algorithm:

1. Same as before, the text file is opened, and its contents are parsed into tokenized words.

2. When a new token is found a word counter is incremented, also same as before.

3. Instead of sorting the base string, it is broken down into its component characters and stored in a table. The table lists how many instances of each character is present. For example, "helloworld" would be stored as:

	```bash
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;d : 1
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;e : 1
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;h : 1
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l : 3
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;o : 2
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;r : 1
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;w : 1
	```

4. Each newly found word token is also broken down character to character, and then the base string table is consulted. If that character's frequency value in the table is greater than zero, the value is decremented by one and the alogrithm proceeds. Otherwise the word is not formable and the algorithm proceeds to the next token. 

5. If the end of the token is sucessfully reached, the formable word counter is incremented.

6. The character table is then cleared to prepare for the next word token,

7. The percentage of formed words is calculated based on the two counters, and returned via the command line. The file is then closed.

What about the computational complexity of the table solution? Each word token needs to be checked with the character table, character by character. Before this can be done, the table needs to be refilled from the base string in order to properly keep track for the frequency of characters. So each check depends on the length of the word token and the length of the base string (call it K). Then if there are N words in the textfile with average length M, the complexity is O(N(K+M)).

A Third Solution
-------

Another solution to this problem has been considered, but not yet included: precomputing all possible formable words from th base string. This would be effcient given a sort base string and a long text file with many words. 

However, the challenge with this method is both computing the power set of the base string and choosing an effcient hash function. Currently this is a work in progress.

The upfront complexity is extremly costly. Generating a power set of char arrays from the base string has complexity of O(2^K), where K is the length of the base string. However, if K is small and the right hash function is chosen, checking a large number of words could be acomplished extremely quickly.

