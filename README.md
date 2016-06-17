WordPercent
=============

This is project that I have been working on in order to better understand fundamental data structures. Here I apply arrays, structs, linked lists, and hash maps in order to solve one problem in a variety of methods.

One of the great things about computer science problems is that there is never just one way to solve them. While every solution may not be equal, they each have their own strengths and weaknesses, which can be explored in detail.

This particular problem is based on a fairly basic programming interview question. However, its different solutions require understanding and clever application of different types of data structures. 

The Challenge
-------

Given a text file, determine the total percentage of words contained within that are formable from a user-inputted base string. Strings are case sensitive. A word is not formable unless all necessary characters are present within the base string.

This includes the frequency of a given character. For example, "Mississippi" is not formable if there is only one "s" character in the base string. At least four separate "s" chars must be present, along with all of the rest of the required letters, in order to form that word.

Four different solutions are included:

1. **Sorting**: The base string and tokenized words from the text file are alphabetized via quick sort and then compared.

2. **Character Tables**: The base string is loaded into a table using a based on it's ASCII table value, and then each tokenized word from the text file is compared with this table.

3. **Precomputing + Sorting**: Every possible formable string is pre-generated from the base string and loaded into a hash map, then tokens from the text file are compared with the map's entries, and sorted if need be.

4. **Precomputing + Character Tables**: Every possible formable character table is pregenerated from the base string and loaded into a hash map, then tokens from the text file are converted to tables themselves and compared with tables from the hash map.


How to execute
-------

First compile the executables using the provided Makefile.

The program operates on the command line. A typical way to execute it would be to type:
`./WordPercent___ S  F`

Where S and F are the base string and the path to the given text-file, respectively. Replace the underline characters with ending of one of the four produced executables (each representing one solution method):

1. WordPercentSort
2. WordPercentTable
3. WordPercentPrecomputeSort
4. WordPercentPrecomputeTable

Then, printed to the command line, will be the percentage of formable words in F.

For example, use the example text file provided and enter:

`./WordPercentTable helloworld /Users/.../example.txt`

The result should be:

```
Base string length: 10
Number of chars read from file: 305
Number of tokenized words read from file: 7
Number of words formable from the base string: 3
Average word length: 43.57
Percent of formable words: 42.86%
```

The two precomputing solutions can optionally take a third input: the number of buckets for the hash map. If no third input is provided, the program defaults to a load factor of approximately 25%.

Assumptions
-------

I consider the following characters to be my tokenizers ``\n \t,.!?\";:()<>{}[]\/_@#$%^&*+=|`~``

Note that the first character represents new line, the second is a space, and the third represents a tab. End of file is also considered. Practically every ASCII symbol other than a letter or number is included-- except for dashes. Microsoft Word considers compound words to be single words, and I have followed that convention as well.

There is no maximum word size for the given text-file, or maximum length of the base string. Each solution takes care of dynamically allocating memory. That said, the precomputing solutions can run into memory limitations if the base string is too lengthy. For more detail about the techniques used for precomputing formable words and storing them in hash maps, please check this related project where I explore the topic in detail: repo.

In the sections below I will go into greater detail about each solution. In terms of time complexity of each solution, I consider three main contributing factors:

1. **K** = The length of the base string
2. **N** = the total number of words within the text-file
3. **M** = the average length of words in the text-file

However, each solution is designed to stop work on a word token if its length exceeds K. So, more often than not the following derived factors will be used to explore complexity:

1. **N<sup>\*</sup>** = the total number of words within the text-file with length <= K
2. **M<sup>\*</sup>** = the average length of words within the text-file with length <= K

Finally, I tend to use the term 'char array' and 'string' interchangeably. Since this project is done in C, all strings are stored as arrays of characters (known as cstrings to C++ programmers).


More On WordPercentSort
-------

This was my first solution to this problem. It focuses on dynamically storing, sorting, and searching through character arrays.

### Basic algorithm:

1. First the text file is opened, and its contents are parsed into tokenized words. A running counter of the word token's length is also kept.

2. When a new tokenizer is found a word counter is incremented and it gets sorted by each character's alphanumeric value using quick sort. If the token's length is greater than that of the base string, the word is unformable and the routine proceeds to the next token.

3. Since the token is sorted, duplicate characters are grouped together. These repeated characters are gathered into another string called partial (since it is a substring of the sorted token). 

4. The base string is also sorted. If the partial string is not a substring of the sorted base string, then the required letters to form the token must not exist within the base string. If this occurs the program moves to the next token.

5. If all partial strings (representing each set of unique characters in the token) exist in the base string, a formed word counter is incremented.

6. The percentage of formed words is calculated based on the two counters, and returned via the command line. The file is then closed.

### Computational Complexity:

This solution needs to sort words N<sup>\*</sup> words using quick sort. Sorting each word this way with exhibits complexity O(M<sup>\*</sup> *log(M<sup>\*</sup>)). However, the computational cost of sorting each string is often overshadowed by the cost of searching for collections of duplicate characters within the sorted base string.

This algorithm uses strstr to accomplish this searching, which has complexity O(K+M<sup>\*</sup>) using GCC. Thus the time complexity of checking a single word token is O(M<sup>\*</sup>*Log(M<sup>\*</sup>)+K+M<sup>\*</sup>), and doing so for the N<sup>\*</sup> words requires O(N<sup>\*</sup>*(M<sup>\*</sup>*Log(M<sup>\*</sup>)+K+M<sup>\*</sup>)).

Since M<sup>\*</sup> <= K, the length of the base string tends to contribute more to the overall complexity. The worst case scenario being where N<sup>\*</sup> = N, M<sup>\*</sup>=M, and M = K. Thus time complexity becomes O(N*K*Log(K)).

More On WordPercentTable
-------

This solution takes advantage of a structs, arrays, and vector-like operations in C.

### Basic algorithm:

1. Instead of sorting the base string, it is broken down into its component characters and stored in a table. The table lists how many instances of each character is present. For example, "helloworld" would be stored as:

	```
	d : 1
	e : 1
	h : 1
	l : 3
	o : 2
	r : 1
	w : 1
	```

This visualization omits characters with zero values.

2. The initial character table is copied into a secondary table that will be used for comparisons. 

3. The text file is opened, and its contents are parsed into individual characters. A word's character length is kept in a running count, with each word assumed at the start to be formable

5. Each character is compared with the secondary base string character table. If that character's frequency value in the table is greater than zero, its value is decremented by one and the algorithm proceeds. Otherwise the word is unformable and the algorithm will continue to read characters until it determines the start of a new token. 

5. If the running character count is non-zero and a tokenizer is read, then the end of the token has been successfully reached. The word token count is incremented. If the word has not been found to be unformable by this point, the formable word counter is incremented. 

6. The running count is reset and secondary base string character table is recopied from the initial table to prepare for the next word token.

7. The percentage of formed words is calculated based on the formable count and the number of word tokens, and returned via the command line. The file is then closed and the memory used for the character tables is freed.

### Computational Complexity:

Each word token needs to be checked with the character table, character by character. Before this can be done, the table needs to be recopied from the base string in order to properly keep track for the frequency of characters. If the table used for comparisons was refilled directly from the base string, it's computation time would depend on the length of the base string. But instead this table is recopied from the original character table, which is filled from reading the base string only once, on initialization. Since the size of the ASCII table is constant at 128 characters, reloading the comparison table requires constant time.

So the time complexity of each individual token comparison is fairly constant, leaving the total time complexity of this solution to be O(N).

Thus WordPercentTable is dependent primarily on the total number of words within the file. This leads to a somewhat unexpected result where, given two files with identical file size, the calculation will complete faster for the file with a larger M. That's because the text-file's size is proportional to N*M, so the file with longer words will also have a fewer total number of words.

More On WordPercentPrecomputeSort
-------

The third solution stores every formable character array within a hash map, with collisions resolved via chaining. As one might imagine, the longer the base string the larger the total amount of formable strings. In fact, the number of char arrays within the hash map increases exponentially with the base string's length. Thus this solution is best suited for cases with short base strings and a larger number of words in the text file.

This method uses a communicative hash function. That means that so long as strings share the same collection of characters, they will be hashed to the same value regardless of ordering. This is useful because it allows the program to only sort strings if there is a possibility that they are formable and their sorted counterparts are present in the hash map.

### Basic algorithm:

1. A hash map is initialized, with each entry able to hold a node structure containing a char array. By default the load factor is approximately 25%, but the number of buckets can be determined manually when the routine is executed.

2. The base string is sorted and its power set is generated. Each char array is saved as a node into the hash map. Nodes are singly linked to facilitate chaining in case of collisions.

3. A buffer char array is initialized in order to compare processed word tokens with the contents of the hash map. 

4. The text file is opened, and its contents is parsed character by character. Each character is added to the buffer, and a running total of the word token length is incremented.

5. If the running word length is nozero and a new tokenizer is encountered, the total word counter is incremented. If the running word length is also less than that of the base string, the completed token string is check with the hash map.

7. If there is a hash map miss then the word is not formable. If there is a hash map hit then the char array is sorted (as in the first solution).

8. Given a hash hit, the sorted string is further checked to see if the two arrays (the one recently filled by the token and the hash map entry) match. If they do then the formable count is incremented. If not the hash map entry is checked for any chained nodes. If they exist this step repeats until either a positive match is found or all chained nodes have been investigated. If no match is found then the formable count is not incremented.

9. At the completion of comparing with the hash map, the buffer array is cleared and the running word length is reset to prepare for the next word token.

10. The percentage of formed words is calculated based on the formable count and the number of word tokens, and returned via the command line. The file is then closed, and then the memory used for the comparison character table and the hash map is freed.

### Computational Complexity:

Because the power set of the base string must be generated, long base strings will result much higher time and space complexities. If the length of the base string is K, then the time complexity for calculating the power set will be O(2^K). 

The lower the load factor on the hash map, the fewer collisions and the faster it will be to fill and read strings from it. This is why the load factor defaults to about 25%, without manually specifying the number of buckets. However, this means that the size of the hash map also scales exponentially: if there are 2^K entries it will default to 2^(K+1)-1 buckets.

Once it comes to using the hash map for comparisons, looking up a stored char array is only O(1). However if the hash map entry is nonempty, the token must be sorted and then each node's char array is compared until a matching string is found or the entry is out of nodes. This comparison method is slightly different than the one done in the first solution: here the routine is checking for exact matches using strncmp rather than searching for matching partial arrays using strstr.

Best case scenario is that there are few collisions. GNU's strncmp function is linear in complexity, which in this context becomes O(M<sup>\*</sup>). When combined with sorting, the complexity of checking a single word token after a hash hit becomes O(M<sup>\*</sup>*Log(M<sup>\*</sup>)+M<sup>\*</sup>). However, only a fraction of the N<sup>\*</sup> words passed through the hash function will actually result in hash hits.

So, as long as the cost of precomputing the base string's power set does not become overwelming and the hash map's load factor is small, this solution should see shorted calculation times than the original sorting solution.

More On WordPercentPrecomputeTable
-------

This fourth solution is very similar to the third, so I won't go over the algorithm step by step. Where it differs is that instead of using char arrays and sorting, it hashes character tables into an array of integers (the hash maps "buckets"). 

The character tables themselves are not stored in the hash map when the power set is generated. If an element of the base string character table's power set gets hashed to a particular bucket, the integer in that location is set to 1. Unfilled buckets remain set to 0.

That way, when a token's character table is looked up within the hash map, a hash hit or miss can be easily determined based on the integer value. However, because of collisions the algorithm cannot be certain that a hash hit guarantees the character table holds a formable word. So, in the case of a hash hit, it then compares the token's character table with a character table formed from the base string. This is done slightly differently than in the initial character table solution, since the routine is checking word by word rather than character by character.

### Computational Complexity:

Like in the previous solution, calculating the power set from the base string has complexity on the order of O(2^K). However comparing character tables in the case of a hash hit is O(1). Thus the complexity of checking for formable words after precomputing will be on the same order as the second solution.

Do you even understand computational complexity anyway?
-------

Not really. I'm still learning the theory, and as it turns out reality can be very different. 

The solutions that use character tables tend to be slower than those using sorted character arrays. This seems strange, since sorting (even quick sort) is more intensive than filling tables. However the GCC functions used for the two sorting solutions are very well optimized, and my character tables probably aren't.
