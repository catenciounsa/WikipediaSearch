#!/bin/bash

#paths and files
files="../data/AsciiAbba/"
stopwords="../data/stopwords/"
target="generated/words-file.txt"

#executing 
../build/src/words/Words FILES=$files STOPWORDS=$stopwords TARGET=$target
