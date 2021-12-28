/**
 * @file search.cpp
 * @author Carlos E. Atencio-Torres (catencio@unsa.edu.pe)
 * @brief 
 * @version 0.1
* @date Dic 2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include "../utils/UtilityFiles.h"
#include "../indexing/MaxKHeap.h"

using namespace std;

void welcomeSearchScriptMessage() {
    cout << "*******************************************" << endl;
    cout << "Welcome to WikipediaSearch " << endl;
    cout << "-------------------------------------------" << endl;
    cout << "This script search for phrases on wikipedia" << endl;
    cout << "*******************************************" << endl;
}

void instructionMessage() {
    cout << "USAGE: Search <params> " << endl;
    cout << "PARAMS:" << endl;
    cout << "  STOPWORDS=/path/to/stopwords/" << endl;
    cout << "  WORDLIST=/path/to/words-file"<< endl;
    cout << "  INDEXFILE=/path/to/index-file"<< endl;
    cout << "EXAMPLE:" << endl;
    cout << "  Search STOPWORDS=stopwords/ INDEXFILE=index.dat" << endl;
    cout << "FOLLOW there will appear a prompt '>' waiting for your phrases" << endl;
    cout << "-------------------------------------------" << endl;
}

void searchWords( const vector<string> &words,
                  map<string,int> &wordIndex,
                  fstream &index ){
    for( const string &word : words ) {
        int wordId = wordIndex[word];
        index.seekg( wordId * sizeof(MaxKHeap) );

        FixedMKH kheap;
        index.read( (char*) &kheap, sizeof(MaxKHeap) );
        cout << "For word: " << word << endl;
        kheap.print();
    }
}


int main(int argc, char **argv) {
    welcomeSearchScriptMessage();
    if( argc != 4 ) {
        instructionMessage();
        return 0;
    }

    // Reading the parameters
    string stopwordsPath, wordlistPath, indexPath;
    
    for(int i=1; i<argc; i++){
        string order = string( argv[i] );
        if( order.rfind("STOPWORDS=")==0 )  stopwordsPath = order.substr(10);
        else if( order.rfind("WORDLIST=")==0 ) wordlistPath = order.substr(9);
        else if( order.rfind("INDEXFILE=")==0 ) indexPath = order.substr(10);
    }

    //Verifiying if the paths come with or without the '/' separator
    if( stopwordsPath[stopwordsPath.size()-1] != '/' ) stopwordsPath = stopwordsPath.substr(0, stopwordsPath.size()-1);

    // Reading the stopwords
    set<string> stopwords = readAllFiles(stopwordsPath);

    // Reading the index of words
    map<string, int> wordIndex = transformIntoIndex(wordlistPath);
    
    // Reading the index file
    fstream index( indexPath, ios::in  | ios::binary );

    // Reading the queries
    string query;
    cout << ">";
    while( getline(cin, query)  ) {
        vector<string> words  = getAllWords(query);
        if( words.size() >  0 ){
            searchWords( words, wordIndex, index );
        } 
        cout << ">";
    }
    
   return 0;
}