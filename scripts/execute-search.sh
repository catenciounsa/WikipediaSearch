#!/bin/bash

#paths and files
stopwords="../data/stopwords/"
wordlist="generated/words-file-treated.txt"
index="generated/wiki.dat"
filenameSize="7"

#executing 
../build/src/search/Search  STOPWORDS=$stopwords WORDLIST=$wordlist INDEXFILE=$index FILENAMESZ=$filenameSize
