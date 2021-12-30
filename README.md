# WikipediaSearch

This project searches words in wikipedia by using a model from an inverted index. The inverted index uses a Heap to keep the most relevant occurreances of a word in a document. The inverted index has a size of **M** x 1024, where **M** is the size of the unique words on Wikipedia.

The project has four parts:
## 1. Preprocessing
- It contains some scripts to preprocess the data downloaded from https://es.wikipedia.org/wiki/Wikipedia:Descargas
- Also contains the results of preprocessing in the folder **Reports**
- The code is in python and c++.
  - Python was choose because of its facility to deal with extend ascii characters.
  - C++ was choose because of its speed to process documents.
- The preprocessing converted files to ascii in lower case. If some files did not match (as chinese documents) were discarted.
- At the end of the preprocessing, only 1607931 files where choosen ( 12GB of data ).

## 2. Words
- It creates the unique list of words

## 3. Indexing
- It creates the inverted index

## 4. Search
- This is a C++ console program that helps the user to search data in wikipedia

## Strategy of Index
- It creates first the inverted index composed by a list of *M* Heaps, each containing up to 1024 occurrences of files. The idea is that it will keep the most frequency appeareances of the word in index $M[i]$
- Then, we visit each file, creating a frequency map **<word,occurences>**. And we proceed to update the index as :
  - Seek wordIndex
  - Recovery the heap
  - Insert the word ocurrence pair 
  - Store the heap
- The complexity was **O(n log(k))** where **k** is the size of the heap. We used 1024 for **k**

## Strategy if Search
- For an entry fo _words[1..n]_ we search the occurrences of each word (if the word is not a stopword or if it exist in the unique word list)
- The query result of each valid word were obtained and we apply a boolean strategy (information retrieval) where we try to find the intersection. It takes ** linear time**.

## How to run it.
- Once the project is downloaded, there is a **compile.sh** fil that will compile all the code
- In the folder *script* will be the scripts. They must be configured first and run in this order:
  - First the **execute-words.sh**. It will generate the unique words.
  - After, the **execute-index.sh**. It will create the index.
  - Finally, the **execute-search.sh**. It will open a prompt to make the queries

## Conclusions
- The creation of the index created a file of 3.9GB and took 18 hours.
- The queries are instantenious

## Future works
- The query does not have a proper treatment. For example UPPERCASE to lowercase. And if a sequence of words is provided, the way that the results are showed must be improved.
