#!/bin/bash

#paths and files
files="../data/Ascii/"
stopwords="../data/stopwords/"
wordlist="generated/words-file-treated.txt"
index="generated/wiki.dat"
filenameSize="2"

#executing 
../build/src/search/Search FILES=$files STOPWORDS=$stopwords WORDLIST=$wordlist INDEXFILE=$index FILENAMESZ=$filenameSize
