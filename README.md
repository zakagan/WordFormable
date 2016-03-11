WordPercent
=============

This C program determines the percent of words from a text file that can be formed from a basis string.

How to execute
-------

The program operates on the command line. A typical way to execute it would be to type:
`./WordPercent S  F`

Where S and F are the basis string and the path to the given textfile, respectively. 
Then, printed to the command line will be the percentage of formable words in F.

For example, you use the example text file provide and enter:
`./WordPercent hellomaybetext /Users/.../example.txt

The result should be:
`Number of tokenized words read from file: 8`
`Number of words formable from the basis string: 4`
`Percent of formable words: 50.00`

Assumptions
-------

I considered the following characters to be my tokenizers `\n ,.!?()<>{}[]\/`
Note that the first char is a new line, and the second is a space. End of file is also considered

There is no maxmium word size within the given textfile. The program dynamically allocates memory based on the basis string.


