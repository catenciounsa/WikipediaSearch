#!/bin/bash

#paths and files
stopwords="../data/stopwords/"
wordlist="generated/words-file.txt"
index="generated/wiki.dat"

#executing 
../build/src/search/Search  STOPWORDS=$stopwords WORDLIST=$wordlist INDEXFILE=$index
