#!/bin/bash

#paths and files
files="../data/AsciiAbba/"
stopwords="../data/stopwords/"
wordlist="generated/words-file.txt"
target="generated/"
partition="2"

#executing 
../build/src/indexing-block/IndexBlock FILES=$files STOPWORDS=$stopwords WORDLIST=$wordlist TARGET=$target PARTITION=$partition
