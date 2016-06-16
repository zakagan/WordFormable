WordPercent
=============

This is project that I have been working on in order to better understand fundamental data structures. Here I apply arrays, structs, linked lists, and hash maps im order to solve one proplem in a variety of methods.

One of the great things about computer science problems is that there is never just one way to solve them. While each solution may not be equal, they each have their own strengths and weaknesses, which we can explore in detail.

This particular problem is based on a fairly basic programming interview question. However, its different solutions require understanding and clever application of different types of data structures. 

The Challenge
-------

Given a text file, determine the toal percentage of words contained within that are formable from a user-inputted base string. Strings are case sensitive. A word is not formable unless all necessary characters are present within the base string.

This includes the frequency of a given character. For example, "Mississippi" is not formable if there is only one "s" character in the base string. At least four seperate "s" chars must be present, along with all of the rest of the required letters, in order to form that word.

Three different solutions are included:

1. **Sorting**: The base string and tokenized words from the text file are alphabetizd via quick sort and then compared.

2. **Character Tables**: The base string is loaded into a table using a based on it's ASCII table value, and then each tokenized word from the text file is compared with this table.

3. **Precomputing + Sorting**: Every possible formable string is pregenerated from the base string and loaded into a hash map, then tokens from the text file are compared with the map's entries, and sorted if need be.

4. **Precomputing + Character Tables**: Every possible formable character table is pregenerated from the base string and loaded into a hash map, then tokens from the text file are converted to tables themselves and compared with tables from the hash map.


How to execute
-------

First compile the executables using the provided Makefile.

The program operates on the command line. A typical way to execute it would be to type:
`./WordPercent___ S  F`

Where S and F are the base string and the path to the given textfile, respectively. Replace the underline characters with ending of one of the two produced executables (each representing one solution method):

1. WordPercentSort
2. WordPercentTable
3. WordPercentPrecomputeSort
4. WordPercentPrecomputeTable

Then, printed to the command line, will be the percentage of formable words in F.

For example, use the example text file provided and enter:

`./WordPercentTable helloworld /Users/.../example.txt`

The result should be:

```
Number of tokenized words read from file: 7
Number of words formable from the base string: 3
Percent of formable words: 42.86
```

The two precomputing solutions can optionally take a third input: the number of buckets for the hash map. If no third input is provided, the program defaults to a load factor of aproximately 25%. For more detail, see the section on WordPercentPrecompute's implementation and complexity.

Assumptions
-------

I consider the following characters to be my tokenizers ``\n \t,.!?\";:()<>{}[]\/_@#$%^&*+=|`~``

Note that the first character represents new line, the second is a space, and the third represents a tab. End of file is also considered. Practically every ASCII symbol other than a letter or number is included-- excpect for dashes. Microsoft Word considers compound words to be single words, and I have followed that convention as well.

There is no maxmimum word size for the given textfile, or maximum length of the base string. Each solution takes care of dynamically allocating memory. 

More On WordPercentSort
-------

This was my first solution to this problem. It focuses on dynamically storing, sorting, and searching through strings.

### Basic algorithm:

1. First the text file is opened, and its contents are parsed into tokenized words. A running counter of the word token's length is also kept.

2. When a new tokenizer is found a word counter is incremented and it gets sorted by each character's alphanumeric value using quick sort. If the token's length is greater than that of the base string, the word is unformable and the rooutine proceeds to the next token.

3. Since the token is sorted, duplicate characters are grouped together. These repeated characters are gathered into another string called partial (since it is a substring of the sorted token). 

4. The base string is also sorted. If the partial string is not a substring of the sorted base string, then the required letters to form the token must not exist within the base string. If this occurs the program moves to the next token.

5. If all partial strings (representing each set of unique characters in the token) exist in the base string, a formed word counter is incremented.

6. The percentage of formed words is calculated based on the two counters, and returned via the command line. The file is then closed.

### Computational Complexity:

Let there be N words in the textfile, each word with average length M. This solution needs to sort all N words using quick sort, with exhibits complexity O(M*log(M)). However, the computational cost of sorting each string is often overshadowed by the cost of searching for collections of duplicate characters within the sorted base string.

This algorithm uses strstr to acomplish this searching, which has complexity O(K+M) using GCC, where K is the length of the base string. Thus the time complexity of the main loop is O(N*(K+M)*M*Log(M)).

In general, M tends to not vary too widely across text files. K however can be very long, in in that case will be the largest contributing factor to this solution's time complexity.

More On WordPercentTable
-------

This solution takes advantage of a structs, arrays, and vector-like operations.

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

This visualization ommits characters with zero values.

2. The inital character table is copied into a secondary table that will be used for comparisons. 

3. The text file is opened, and its contents are parsed into individual characters. A word's character length is kept in a running count, with each word assumed at the start to be formable

5. Each character is compared with the secondary base string character table. If that character's frequency value in the table is greater than zero, its value is decremented by one and the alogrithm proceeds. Otherwise the word is unformable and the algorithm will continue to read characters until it determines the start of a new token. 

5. If the running character count is non-zero and a tokenizer is read, then the end of the token has been sucessfully reached. The word token count is incremented. If the word has not been found to be unformable by this point, the formable word counter is incremented. 

6. The running count is reset and secondary base string character table is recopied from the initial table to prepare for the next word token.

7. The percentage of formed words is calculated based on the formable count and the number of word tokens, and returned via the command line. The file is then closed and the memory used for the character tables is freed.

### Computational Complexity:

Each word token needs to be checked with the character table, character by character. Before this can be done, the table needs to be recopied from the base string in order to properly keep track for the frequency of characters. If the table used for comparisions was refilled directly from the base string, it's computation time would depend on the length of the base string. But instead this table is recopied from the orginal character table, which is filled from reading the base string only once, on initialization. Since the size of the ASCII table is constant at 128 characters, reloading the comparision table requires constant time.

So each check within the main loop depends on the average length of words within the text file M. Then if there are N words in the textfile, the complexity is O(N*M).

More On WordPercentPrecompute
-------

The third solution stores every formable character table within a hash map, with collisions resolved via chaining. As one might imagine, the longer the base string the larger the total amount of formable character tables. In fact, the number of tables within the hash map increases exponentially with the base string's length. Thus this solution is best suited for cases with short base strings and a larger number of words in the text file.

### Basic algorithm:

1. A hash map is intialized, with each entry able to hold a node structure containing a character table. By default the load factor is aproximately 25%, but the number of buckets can be determined manually when the routine is executed.

2. The power set of the base string character table is generated, and each element is saved into the hash map. This algorithm is a slight varietion of another of my C projects. For more detail on calculating the power set of strings, see this repo: PowerSetString.

3. A character table is initalized in order to compare processed word tokens with the contents of the hash map. 

4. The text file is opened, and its contents is parsed character by character. Each character is added to the character table, and a running total of the word token length is incremented.

5. If the running word length is nozero and a new tokenizer is encountered, the total word counter is incremented. If the running word length is also less than that of the base string, the character table that was being filled is then checked with the hasp map.

7. If there is a hash map miss then the word is not formable. If there is a hash map hit then the entry is further checked to see if the two tables (the one recently filled by the token and the hash map entry) match. If they do then the formable count is incremented. If not the hash map entry is checked for any chained nodes (caused by collisions to this hash map entry). If they exist this step repeats until either a positive match is found or all chained nodes have been investifated. If no match is found then the formable count is not incremented.

8. At the completion of comparing with the hash map the character table is cleared and the running word length is reset to prepare for the next word token.

9. The percentage of formed words is calculated based on the formable count and the number of word tokens, and returned via the command line. The file is then closed, and then the memory used for the comparision character table and the hash map is freed.

### Computational Complexity:

Because the power set of the base string must be generated, long base strings will result much higher time and space complexities. If the length of the base string is K, then the time complexity for claculating the power set will b O(2^K). 

The lower the load factor on the hash map, the fewer collisions and the faster it will be to fill and read character tables from it. This is why the load factor defaults to about 25%, without manually specifying the number of buckets. However, this means that the size of the hash map also scales exponentially: if there are 2^K entries it will default to (2^(K+1))-1 buckets.

Once it comes to using the hash map for comparisions, looking up a character table is only O(1). However if the hash map entry is nonempty, each node's character table must be compared until a matching table is found or the entry is out of nodes. 

Best case scenario is that there are few collisions. If there are a low number of formable words within the textfile, 

