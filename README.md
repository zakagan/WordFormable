WordFormable
=============

Computing gives us several tools for comparing and analyzing different solutions to the same problem. In this repo I explore one fairly straight-forward computer science problem, as well as five separate solutions to it.

While all solutions are not equal, each one presented has its own strengths and weaknesses. Through them I explore different types of basic data structures and their uses.

The actual programming for this project comes in three parts:

1. The actual executables that solve the problem (detailed below), written in C

2. The testing scripts used to generate data to compare the different solutions, written in Bash

3. The plotting scripts used to the graph the results of testing data, written in Python.

The Problem
-------

Given a text file, determine all the words contained within that are formable from a user-inputted base string. Strings are case sensitive. A word is not formable unless all necessary characters are present within the base string.

This includes the frequency of a given character. For example, "Mississippi" is not formable if there is only one "s" character in the base string. At least four separate "s" chars must be present, along with all of the rest of the required letters, in order to form that word.

I sometimes describe this as the "scrabble problem". Imagine you are playing a version of scrabble in which the dictionary of valid words could change every game. How could you determine what valid words you could play, given your tiles and the specific dictionary being used?

The real challenge of this problem lies with efficiently determining the formability of a word token. This project explores five different methods:

1. **Searching For Partials**: The base string and tokenized words from the text file are alphabetized via quick sort. Then subsections of the token are searched for within the sorted base string.

2. **Character Tables**: The base string is loaded into a table using a based on it's ASCII table value, and then each tokenized word from the text file is compared with this table.

3. **Hash Map and Comparing**: Every possible formable string is pre-generated from the base string and loaded into a hash map, then tokens from the text file are compared with the map's entries.

4. **Hash Map and Searching For Partials**: Every possible formable character table is pre-generated from the base string and then used to generate a hash map of validity values. Each token is looked up within the hash map, and if there's a hit the token is sorted and its subsections are searched for, just as in solution 1.

5. **Bi-Directional Queue**: A doubly-linked list is generated from the sorted base string. Every character within a particular token is searched for along the bi-directional queue. When a match is found, that char's node is removed from the queue. This proceeds until a token's char cannot be found or the all the characters in the token have been checked.

How To Execute
-------

First compile the executables using the provided Makefile.

The program operates on the command line. A typical way to execute it would be to type:
`./WordPercent___ S  F`

Where S and F are the base string and the path to the given text-file, respectively. Replace the underline characters with ending of one of the four produced executables (each representing one solution method):

1. WordFormablePartials
2. WordFormableTable
3. WordFormablePowerString
4. WordFormablePowerVInts
5. WordFormableQueueSearch

Then, printed to the command line, will be the formable word tokens along with some additional data.

For example, use the example text file provided and enter:

`./WordPercentTable helloworld /Users/.../example.txt`

The result should be:

```
Formable words within the provided textfile:
world
hello
hello
Base string length: 10
Number of chars read from file: 305
Number of tokenized words read from file: 7
Number of words formable from the base string: 3
Average word length: 43.57
Percent of formable words: 42.86%
```

There are a couple of optional inputs. The third input will silence the printing of each formable word token if set to 1 (and won't silence anything if set to 0). The two power-set/hash-map solutions can optionally take a fourth input: the number of buckets for the hash map. If no fourth input is provided, the program defaults to a load factor of approximately 25%.

Using these optional inputs looks like this:

```
./WordPercentPowerHP helloworld /Users/.../example.txt 0 100
Base string length: 10
Number of chars read from file: 305
Number of tokenized words read from file: 7
Number of words formable from the base string: 3
Average word length: 43.57
Percent of formable words: 42.86%
```

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

1. **N<sub>k</sub>** = the total number of words within the text-file with length <= K
2. **M<sub>k</sub>** = the average length of words within the text-file with length <= K

Finally, I tend to use the term 'char array' and 'string' interchangeably. Since this project is done in C, all strings are stored as arrays of characters (known as cstrings to C++ programmers).

Charts
-------

Using the test scripts included, data was collected and then plotted using Python's matplotlib. More tests should be run (running the testing scripts multiple times and combining the data), but what follows are the preliminary results.

### Number of Words

![alt tag](https://github.com/zakagan/WordFormable/blob/master/images/num_words.png)

This chart demonstrates the increase in computation time as the number of words in the dictionary file increases.

The words being read  come from the file of words used for spell checking on unix/linux machines (`/usr/share/dict/words`). That means these results reflect a likely case scenario of scanning a dictionary with a variety of words (different lengths, character variety, etc.). The base string is a random 10 character word, which is kept constant as the size of the dictionaries increase.

### Length of Base String (Average Case)

![alt tag](https://github.com/zakagan/WordFormable/blob/master/images/len_base.png)

This chart demonstrates the increase in computation time as the length of the base string increases.

The dictionary here is constant across different trials (again taken from the spell checking dictionary). Each solution uses the same base string of a specific length.

### Length of Base String (Worst Case)

![alt tag](https://github.com/zakagan/WordFormable/blob/master/images/worst_case_z.png)

This chart models the same situation as above, but instead all of the words in the dictionary 100% match the base string. This means every character must be checked. Each dictionary file used has the same number of words, however across trials the length of the words increase to match the growth of the base string. 

### Load Factor of Hash Map Solutions

![alt tag](https://github.com/zakagan/WordFormable/blob/master/images/load_factor.png)

This chart demonstrates the increase in computation time as the load factor increases (higher load factor means fewer buckets in the hash table).

More On WordPercentPartials
-------

This was my first solution to this problem. It focuses on dynamically storing, sorting, and searching through character arrays.

### Basic algorithm:

1. First the text file is opened, and its contents are parsed into tokenized words. A running counter of the word token's length is also kept.

2. When a new tokenizer is found a word counter is incremented. If the token's length is greater than that of the base string, the word is unformable and the routine proceeds to the next token. Otherwise it gets sorted by each character's alphanumeric value using quick sort.

3. Since the token is sorted, duplicate characters are grouped together. These repeated characters are gathered into another string called partial (since it is a substring of the sorted token). 

4. The base string is also sorted. If the partial string is not a substring of the sorted base string, then the required letters to form the token must not exist within the base string. If this occurs the program moves to the next token.

5. If all partial strings (representing each set of unique characters in the token) exist in the base string, a formed word counter is incremented.

6. The percentage of formed words is calculated based on the two counters, and returned via the command line. The file is then closed.

### Computational Complexity:

This solution needs to sort words N<sub>k</sub> words using quick sort. Sorting each word this way with exhibits complexity O(M<sub>k</sub>\*log(M<sub>k</sub>)). However, the computational cost of sorting each string is often overshadowed by the cost of searching for collections of duplicate characters within the sorted base string.

This algorithm uses strstr to accomplish this searching, which has complexity O(K+M<sub>k</sub>) using GCC. Thus the time complexity of checking a single word token is O(M<sub>k</sub>\*Log(M<sub>k</sub>)+(K+M<sub>k</sub>)), and doing so for the N<sub>k</sub> words requires O(N<sub>k</sub>\*(M<sub>k</sub>*Log(M<sub>k</sub>)+(K+M<sub>k</sub>))).

Since M<sub>k</sub> <= K, the length of the base string tends to contribute more to the overall complexity. The worst case scenario being where N<sub>k</sub> = N, M<sub>k</sub>=M, and M = K. Thus the time complexity becomes O(N\*(K\*Log(K)+K)).

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

This visualization omits characters with zero values. The table has slots for each possible character.

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

More On WordPercentPowerString
-------

The third solution stores every formable character array (generated via a power set of the base string) within a hash map, with collisions resolved via chaining. As one might imagine, the longer the base string the larger the total amount of formable strings. In fact, the number of char arrays within the hash map increases exponentially with the base string's length. Thus this solution is best suited for cases with short base strings and a larger number of words in the text file.

This method uses a communicative hash function. That means that so long as strings share the same collection of characters, they will be hashed to the same value regardless of ordering. This is useful because it allows the program to only sort strings if there is a possibility that they are formable and their sorted counterparts are present in the hash map.

### Basic algorithm:

1. A hash map is initialized, with each entry able to hold a node structure containing a char array. By default the load factor is approximately 25%, but the number of buckets can be determined manually when the routine is executed.

2. The base string is sorted and its power set is generated. Each char array is saved as a node into the hash map. Nodes are singly linked to facilitate chaining in case of collisions.

3. A buffer char array is initialized in order to compare processed word tokens with the contents of the hash map. 

4. The text file is opened, and its contents is parsed character by character. Each character is added to the buffer, and a running total of the word token length is incremented.

5. If the running word length is non-zero and a new tokenizer is encountered, the total word counter is incremented. If the running word length is also less than that of the base string, the completed token string is check with the hash map.

7. If there is a hash map miss then the word is not formable. If there is a hash map hit then the char array is sorted (as in the first solution).

8. Given a hash hit, the sorted string is further checked to see if the two arrays (the one recently filled by the token and the hash map entry) match. If they do then the formable count is incremented. If not the hash map entry is checked for any chained nodes. If they exist this step repeats until either a positive match is found or all chained nodes have been investigated. If no match is found then the formable count is not incremented.

9. At the completion of comparing with the hash map, the buffer array is cleared and the running word length is reset to prepare for the next word token.

10. The percentage of formed words is calculated based on the formable count and the number of word tokens. It is reported to the command line, the file is then closed, and then the memory used for the comparison character table and the hash map is freed.

### Computational Complexity:

Because the power set of the base string must be generated, long base strings will result much higher time and space complexities. If the length of the base string is K, then the time complexity for calculating the power set will be O(2^K). 

The lower the load factor on the hash map, the fewer collisions and the faster it will be to fill and read strings from it. This is why the load factor defaults to about 25%, without manually specifying the number of buckets. However, this means that the size of the hash map also scales exponentially: if there are 2^K entries it will default to 2^(K+1)-1 buckets.

Once it comes to using the hash map for comparisons, looking up a stored char array is only O(1). However if the hash map entry is nonempty, the token must be sorted and then each node's char array is compared until a matching string is found or the entry is out of nodes. This comparison method is slightly different than the one done in the first solution: here the routine is checking for exact matches using strncmp rather than searching for matching partial arrays using strstr.

Best case scenario is that there are few collisions. GNU's strncmp function is linear in complexity, which in this context becomes O(M<sub>k</sub>). When combined with sorting, the complexity of checking a single word token after a hash hit becomes O(M<sub>k</sub>\*Log(M<sub>k</sub>)+M<sub>k</sub>). However, only a fraction of the N<sub>k</sub> words passed through the hash function will actually result in hash hits.

So, as long as the cost of precomputing the base string's power set does not become overwhelming and the hash map's load factor is small, this solution should see shorter calculation times than the original sorting solution.

More On WordPercentPowerVInts
-------

This fourth solution is very similar to the third, so I won't go over the algorithm step by step. Where it differs is that instead of storing the character arrays themselves into the hasp map, it stores a validity integer. That means a bucket in the hash map will hold a 1 if an element of the power set was hashed there, and 0 otherwise.

Because of collisions it is not enough to simply look up a token within the validity hash map. If there is a hash hit the token is then compared with the base string using the same sorting technique used in the first solution (WordPercentPartials). However a hash map miss does guarantee that a token is not formable.

### Computational Complexity:

Like in the previous solution, calculating the power set from the base string has complexity on the order of O(2^K). Then comparing the token with the base string has complexity O(M<sub>k</sub>\*Log(M<sub>k</sub>)+(K+M<sub>k</sub>)), from the first solution.

However, so long as K is small these factors do not become a major issue. Looking up tokens in the hash map is O(1) in time, and so long as not all of the words in the dictionary are formable there should be significant time savings when compared with WordFormablePartials.

More On WordPercentQueueSearch
-------

The fifth solution uses a bi-directional queue to keep track of all of the characters in the base string. As a token is compared with the base string, character nodes are disconnected from the bi-directional queue. When a character node can no longer be found, the token is unformable. However if the end of the token is reached without missing a character node, the word is formable.

### Basic algorithm:

1. The base string is sorted and then loaded into a bi-directional queue, with nodes for each character. An index is kept so that the connections/edges can be reformed after each token.

2. The text file is opened, and its contents are parsed into tokenized words. A running counter of the word token's length is also kept.

3. When a new tokenizer is found a word counter is incremented. It is not sorted. If the token's length is greater than that of the base string, the word is unformable and the routine proceeds to the next token.

3. The first character of the token is then compared with the middle character of the bi-directional queue. If the token's character is earlier in the alphabet the queue is searched up. Otherwise the queue is searched down. In either case, if the end of the queue is reached then the token is unformable. If the right character node is found it is then removed from the queue, and the next character in the token is searched in the same way, starting from this new place in the queue.

4. This process continues until all of the characters in the token have been found or the token is determined to be unformable (in which case the formed word counter is incremented).

5. Using the index, the bi-directional queue is reformed and the next token is checked.

6. The percentage of formed words is calculated based on the two counters, and returned via the command line. The queue is freed and the file is then closed.

### Computational Complexity:

The worse case scenario is when the token is itself the base string and all characters must be looked up. For the first character at most half of the bi-directional queue will be traversed. This continues for every character, but the queue gets smaller and smaller as more character nodes are removed.

Resetting the bi-directional queue is dependent on the length of the base string, but is the same after each token. The limiting factor here is the process of crawling along the queue data structure.

Other Solutions
-------

More advanced AIs for Scrabble-like games use more complicated data structures in order to find words, like DAWGs and GADDAGs. Those data structures are both refinements of a data structure called tries. A trie is like a tree except instead of storing keys in the nodes, the keys (or words strings) are stored based on the position in the trie.

The best way to understand the concept is to look at a visual representation of an example trie.

![alt tag](https://github.com/zakagan/WordFormable/blob/master/images/250px-Trie_example.svg.png)

A trie for keys "A","to", "tea", "ted", "ten", "i", "in", and "inn", taken from [the wikipedia page on the trie data structure](https://en.wikipedia.org/wiki/Trie).

Moving from the root node down, more and more of the word becomes spelled out. The leaves themselves represent each of the formable words.

Thus a possible solution for the scrabble problem is to load the entire dictionary into a trie and then search for formable words by traveling towards using a table of characters from the base string. This proves to be very fast as searching through strings is quit time efficient.

However loading the dictionary into a trie can take up a lot of space. Both DAWGs and GAGDAGs are designed to reduce any redundant paths from the trie (for example, formable words are no longer given each their own leaf, so "cats" and "cat" do not form separate branches).

Future work on this project could involve implementing a trie-based solution for dictionary loading and searching formable words.

For more info on how DAWGs and GAGDAGs can be used to solve scrabble-like word forming problems, see these academic papers:

1. [The World’s Fastest Scrabble Program by ANDREW W. APPEL AND GUY J. JACOBSON](https://pdfs.semanticscholar.org/da31/cb24574f7c881a5dbf008e52aac7048c9d9c.pdf) (DAWGs)

2. [A Faster Scrabble Move Generation Algorithm by STEVEN A. GORDON](http://ericsink.com/downloads/faster-scrabble-gordon.pdf) (GADDAGs)

