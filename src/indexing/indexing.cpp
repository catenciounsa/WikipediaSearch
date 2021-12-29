/**
 * @file indexing.cpp
 * @author Carlos E. Atencio-Torres (catencio@unsa.edu.pe)
 * @brief 
 * @version 0.1
 * @date Dic 2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <set>
#include <vector>
#include <filesystem>
#include <chrono>
#include <ctime>
#include "../utils/UtilityFiles.h"
#include "MaxKHeap.h"

#define INDEX_FILENAME "wiki.dat"

using namespace std;


void welcomeIndexScriptMessage() {
    cout << "***************************************" << endl;
    cout << "Welcome to WikipediaSearch " << endl;
    cout << "----------------------------------------" << endl;
    cout << "This script creates the index of words" << endl;
    cout << "***************************************" << endl;
}

void instructionMessage() {
    cout << "USAGE: Indexing <params> " << endl;
    cout << "PARAMS:" << endl;
    cout << "  FILES=/path/from/files/" << endl;
    cout << "  STOPWORDS=/path/to/stopwords/" << endl;
    cout << "  WORDLIST=/path/to/words-file"<< endl;
    cout << "  TARGET=/path/to/index/"<< endl;
    cout << "EXAMPLE:" << endl;
    cout << "  Index FILES=files/ STOPWORDS=stopwords/ WORDLIST=words-file.txt TARGET=index/" << endl;
}

bool createFileIndex( const vector<string> &wordlist, const string &targetPath ) {
    ofstream target( targetPath+string(INDEX_FILENAME), ios::out | ios::binary );
    if( !target ) {
        cout << "Error opening file" << endl; return false;
    }
    cout << "Wordlist has size of " << wordlist.size() << endl;
    for (int i = 0; i < wordlist.size(); i++){
        //FixedMKH tmp;
        OptimizedMaxKHeap tmp;
        target.write( (char*) &tmp, sizeof(OptimizedMaxKHeap) );
    }
    target.close();
    return true;
}

map<int,int> readFrequency(const string &filename, 
                              map<string,int> &wordIndex,
                              const set<string> &stopwords) {
    ifstream file(filename);
    map<int,int> msi;

    string line;
    while( getline(file,line) ) {
        vector<string> words = getAllWords(line);
        for( const string &word : words ) {
            if( stopwords.count(word) == 0 && !isStopWord(word) ) {
                msi[ wordIndex[word] ] ++;
            }
        }
    }

    return msi;
}

/**
 * @brief Updates the index file.
 * 
 * @param index FSTREAM
 * @param fileId  number of file
 * @param frequency map of frequency
 */
void updateIndex(fstream &index, int fileId, map<int,int> &frequency ) {
    for( const pair<int,int> &keyval : frequency ) {
        int wordIndex = keyval.first;
        int freqVal = keyval.second;
        index.seekg( wordIndex * sizeof(MaxKHeap) );

        //FixedMKH kheap;
        OptimizedMaxKHeap kheap;
        index.read( (char*) &kheap, sizeof(MaxKHeap) );
        
        kheap.insert(fileId, freqVal);

        index.seekp( wordIndex * sizeof(MaxKHeap) );
        index.write( (char*) &kheap, sizeof(MaxKHeap) );
    }
}

int main(int argc, char **argv) {
    welcomeIndexScriptMessage();
    if( argc != 5 ) {
        instructionMessage();
        return 0;
    }

    // Reading the parameters
    string fromPath, stopwordsPath, wordlistPath, targetPath;
    
    for(int i=1; i<argc; i++){
        string order = string( argv[i] );
        if( order.rfind("FILES=")==0 ) fromPath = order.substr(6);
        else if( order.rfind("STOPWORDS=")==0 )  stopwordsPath = order.substr(10);
        else if( order.rfind("WORDLIST=")==0 ) wordlistPath = order.substr(9);
        else if( order.rfind("TARGET=")==0 ) targetPath = order.substr(7);
    }

    //Verifiying if the paths come with or without the '/' separator
    if( fromPath[fromPath.size()-1] != '/' ) fromPath = fromPath.substr(0, fromPath.size()-1);
    if( stopwordsPath[stopwordsPath.size()-1] != '/' ) stopwordsPath = stopwordsPath.substr(0, stopwordsPath.size()-1);
    if( targetPath[targetPath.size()-1] != '/' ) targetPath = targetPath.substr(0, targetPath.size()-1);

    // Reading the stopwords
    set<string> stopwords = readAllFiles(stopwordsPath);

    // Read the wordlist
    vector<string> wordlist = readLinesFrom(wordlistPath);
    map<string,int> wordIndex = transformIntoIndex(wordlistPath);

    // Creates the file index
    auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
    cout << "Starting... " << ctime(&timenow) << endl;
    bool successCreated = createFileIndex(wordlist, targetPath);

    if( successCreated ) {
        cout << "Great, index created in " << endl;
        cout << " " << targetPath << INDEX_FILENAME << endl;
    }

    // Fill the index 
    fstream index( targetPath + INDEX_FILENAME, ios::in | ios::out | ios::binary );
    vector<string> files;
    readFiles(fromPath, files);
    int nFiles = 0;
    int jump = files.size() / 100;
    if( jump == 0 ) jump = 1;
    int percentage = 1;
    for( const string &filename : files) {
        int fileId = atoi( filename.substr( 0, filename.size()-4 ).c_str() ); //"0001.txt => 1"
        map<int,int> frequency = readFrequency( fromPath + filename, wordIndex, stopwords );
        
        updateIndex(index, fileId, frequency);
        if( (percentage<100) && (((nFiles++)%jump ) == 0)) {
            timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
            cout << percentage << "%: " << nFiles << " proceseed / " << ctime(&timenow);
            percentage+=1;
        }
    }
    cout << "Processed 100% " << files.size() << endl;

    cout << "Great, the index was updated" << endl;

    return 0;
}