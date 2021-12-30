#!/bin/bash

#paths and files
files="/media/carlos/Acer/Documents\ and\ Settings/carat/Mis\ documentos/DOCTORADO/EstructuraDatos/Wikipedia/Ascii/"
stopwords="../data/stopwords/"
target="generated/words-file.txt"

#executing 
../build/src/words/Words FILES=$files STOPWORDS=$stopwords TARGET=$target
