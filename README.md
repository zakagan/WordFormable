WordPercent
=============

This C program determines the percent of words from a text file that can be formed from a base string.

How to execute
-------

The program operates on the command line. A typical way to execute it would be to type:
`./WordPercent S  F`

Where S and F are the base string and the path to the given textfile, respectively. Then, printed to the command line, will be the percentage of formable words in F.

For example, you use the example text file provided and enter:

`./WordPercent hellomaybetext /Users/.../example.txt`

The result should be:

`Number of tokenized words read from file: 8`

`Number of words formable from the base string: 4`

`Percent of formable words: 50.00`

Assumptions
-------

I considered the following characters to be my tokenizers `\n ,.!?()<>{}[]\/`

Note that the first char is a new line, and the second is a space. End of file is also considered.

There is no maxmimum word size within the given textfile. The program dynamically allocates memory according to the length of the base string.

Brief Summary of the implementation
-------

1. First the text file is opened, and its contents are parsed into tokenized words.

2. When a new token is found a word counter is incremented and it gets sorted by each character's alphanumeric value using quick sort.

3. Since the token is sorted, duplicate characters are grouped together. These repeated characters are gathered into another string called partial (since it is a substrig of the sorted token). 

4. The base string is also sorted. If the partial string is not a substring of the sorted base string, then the required letters to form the token must not exist within the base string. If this occurs the program moves to the next token.

5. If all partial strings (representing each set of unique characters in the token) exist in the base string, a formed word counter is incremented.

6. The percentage of formed words is calculated based on the two counters, and returned via the command line. The file is then closed.
