#!/bin/bash

#paths and files
files="../data/AsciiAbba/"
stopwords="../data/stopwords/"
wordlist="generated/words-file.txt"
target="generated/"

#executing 
../build/src/indexing/Index FILES=$files STOPWORDS=$stopwords WORDLIST=$wordlist TARGET=$target
