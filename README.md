WordPercent
=============

Solving one problem using multiple different methods can be a great learning experience. No where is that more apparent than in computer science, where different algorithmic solutions can be analyzed in detail.

This particular problem is based on a fairly basic programming interview question. However, its different solutions require understanding and clever application of different types of data structures. 

The Challenge
-------

Given a text file, determine the toal percentage of words contained within that are formable from a user-inputted base string. Strings are case sensitive. A word is not formable unless all necessary characters are present within the base string.

This includes the frequency of a given character. For example, "Mississippi" is not formable if there is only one "s" character in the base string. At least four seperate "s" chars must be present, along with all of the rest of the required letters, in order to form that word.

Three different solutions are included:

1. **Sorting**: The base string and tokenized words from the text file are alphabetizd via quick sort and then compared.

2. **Character Tables**: The base string is loaded into a table using a based on it's ASCII table value, and then each tokenized word from the text file is compared with this table.

3. **Precomputing**: Extending from the previous solution, every possible character table is pregenerated from the base string and loaded into a hash map, then tokens from the text file are compared with the map's entries.

How to execute
-------

First compile the executables using the provided Makefile.

The program operates on the command line. A typical way to execute it would be to type:
`./WordPercent___ S  F`

Where S and F are the base string and the path to the given textfile, respectively. Replace the underline characters with ending of one of the two produced executables (each representing one solution method):

1. WordPercentSort
2. WordPercentTable
3. WordPercentPrecompute

Then, printed to the command line, will be the percentage of formable words in F.

For example, you use the example text file provided and enter:

`./WordPercentTable helloworld /Users/.../example.txt`

The result should be:

```
Number of tokenized words read from file: 7
Number of words formable from the base string: 3
Percent of formable words: 42.86
```

WordPercentPrecompute can optionally take a third input: the number of buckets for the hash map. If no third input is provided, the program defaults to a load factor of aproximately 25%. For more detail, see the section on WordPercentPrecompute's implementation and complexity.

Assumptions
-------

I consider the following characters to be my tokenizers ``\n \t,.!?\";:()<>{}[]\/_@#$%^&*+=|`~``

Note that the first char is a new line, and the second is a space. End of file is also considered. Practically every ASCII symbol other than a letter or number is included-- excpect for dashes. Microsoft Word considers compound words to be single words, and I have followed that convention as well.

There is no maxmimum word size for the given textfile, or maximum length of the base string. Each solution takes care of dynamically allocating memory. 

More On WordPercentSort
-------

This was my first solution to this problem. It focuses on dynamically storing, sorting, and searching through strings.

### Basic algorithm:

1. First the text file is opened, and its contents are parsed into tokenized words.

2. When a new token is found a word counter is incremented and it gets sorted by each character's alphanumeric value using quick sort.

3. Since the token is sorted, duplicate characters are grouped together. These repeated characters are gathered into another string called partial (since it is a substring of the sorted token). 

4. The base string is also sorted. If the partial string is not a substring of the sorted base string, then the required letters to form the token must not exist within the base string. If this occurs the program moves to the next token.

5. If all partial strings (representing each set of unique characters in the token) exist in the base string, a formed word counter is incremented.

6. The percentage of formed words is calculated based on the two counters, and returned via the command line. The file is then closed.

### Computational Complexity:

Let there be N words in the textfile, each word with average length M. This solution needs to sort all N words using quick sort, so its complexity is O(NMlog(M)).

More On WordPercentTable
-------

This solution takes advantage of a structs, arrays, and vector-like operations.

### Basic algorithm:

1. Same as before, the text file is opened, and its contents are parsed into tokenized words.

2. When a new token is found a word counter is incremented, also same as before.

3. Instead of sorting the base string, it is broken down into its component characters and stored in a table. The table lists how many instances of each character is present. For example, "helloworld" would be stored as:

	```
	d : 1
	e : 1
	h : 1
	l : 3
	o : 2
	r : 1
	w : 1
	```

4. Each newly found word token is also broken down character to character, and then the base string table is consulted. If that character's frequency value in the table is greater than zero, the value is decremented by one and the alogrithm proceeds. Otherwise the word is not formable and the algorithm proceeds to the next token. 

5. If the end of the token is sucessfully reached, the formable word counter is incremented.

6. The base string character table recopied to prepare for the next word token.

7. The percentage of formed words is calculated based on the two counters, and returned via the command line. The file is then closed.

### Computational Complexity:

Each word token needs to be checked with the character table, character by character. Before this can be done, the table needs to be refilled from the base string in order to properly keep track for the frequency of characters. So each check depends on the length of the word token and the length of the base string (call it K). Then if there are N words in the textfile with average length M, the complexity is O(N(K+M)).

More On WordPercentPrecompute
-------

The third solution stores character tables within a hash map. Collisions are resolved via chaining.

### Basic algorithm:

### Computational Complexity:

