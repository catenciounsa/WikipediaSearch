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

#define INDEX_FILENAME "wiki"

using namespace std;

void welcomeIndexScriptMessage() {
    cout << "***************************************" << endl;
    cout << "Welcome to WikipediaSearch " << endl;
    cout << "----------------------------------------" << endl;
    cout << "This script creates the index of words" << endl;
    cout << "***************************************" << endl;
}

void instructionMessage() {
    cout << "USAGE: IndexBlock <params> " << endl;
    cout << "PARAMS:" << endl;
    cout << "  FILES=/path/from/files/" << endl;
    cout << "  STOPWORDS=/path/to/stopwords/" << endl;
    cout << "  WORDLIST=/path/to/words-file"<< endl;
    cout << "  TARGET=/path/to/index/"<< endl;
    cout << "  PARTITION=number of partitions" << endl;
    cout << "EXAMPLE:" << endl;
    cout << "  IndexBlock FILES=files/ STOPWORDS=stopwords/ WORDLIST=words-file.txt TARGET=index/ PARTITION=2" << endl;
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
                if( wordIndex.count(word) != 0 )
                    msi[ wordIndex[word] ] ++;
            }
        }
    }

    return msi;
}

void serialize( vector<MaxKHeap> &maxKheaps, const string &filename ) {
    fstream index( filename, ios::app | ios::binary );
    for(int i=0; i< maxKheaps.size(); i++ ) {
        index.write( (char*) &maxKheaps[i], sizeof(OptimizedMaxKHeap) );
    }
    index.close();
}

void indexBlock(vector<string> &vec, 
                const string &fromPath, 
                const string &targetPath,
                vector<string> &files,
                set<string> &stopwords) {
    auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
    cout << "Creating a block" << ctime( &timenow ) << endl;

    // Create the wordIndex
    map<string,int> wordIndex;
    for( int i=0; i<vec.size(); i++)
        wordIndex[ vec[i] ] = i;

    // Creating the Heaps on memory
    vector< MaxKHeap > maxHeaps;
    for( int i=0; i< vec.size(); i++ )
        maxHeaps.push_back( OptimizedMaxKHeap() );

    // Updating the heaps
    int nFiles = 0;
    int jump = files.size() / 100;
    if( jump == 0 ) jump = 1;
    int percentage = 1;
    for( const string &filename : files) {
        int fileId = atoi( filename.substr( 0, filename.size()-4 ).c_str() ); //"E.g. 0001.txt => 1"
        map<int,int> frequency = readFrequency( fromPath + filename, wordIndex, stopwords );

        //Update the heap
        for( const pair<int,int> &keyval : frequency ) {
            int wordIndex = keyval.first;
            int freqVal = keyval.second;

            maxHeaps[wordIndex].insert( fileId, freqVal );
        }
        
        // For print purposes
        if( (percentage<100) && (((nFiles++)%jump ) == 0)) {
            timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
            cout << percentage << "%: " << nFiles << " proceseed / " << ctime(&timenow);
            percentage+=1;
        }
    }
    cout << "Processed 100% " << files.size() << endl;

    serialize( maxHeaps, targetPath );
}

int main(int argc, char **argv) {
    welcomeIndexScriptMessage();
    if( argc != 5 ) {
        instructionMessage();
        return 0;
    }

    // Reading the parameters
    string fromPath, stopwordsPath, wordlistPath, targetPath;
    int npartition;
    
    for(int i=1; i<argc; i++){
        string order = string( argv[i] );
        if( order.rfind("FILES=")==0 ) fromPath = order.substr(6);
        else if( order.rfind("STOPWORDS=")==0 )  stopwordsPath = order.substr(10);
        else if( order.rfind("WORDLIST=")==0 ) wordlistPath = order.substr(9);
        else if( order.rfind("TARGET=")==0 ) targetPath = order.substr(7);
        else if( order.rfind("PARTITION=")==0 ) npartition = atoi( order.substr(10).c_str() );
    }

    //Verifiying if the paths come with or without the '/' separator
    if( fromPath[fromPath.size()-1] != '/' ) fromPath = fromPath.substr(0, fromPath.size()-1);
    if( stopwordsPath[stopwordsPath.size()-1] != '/' ) stopwordsPath = stopwordsPath.substr(0, stopwordsPath.size()-1);
    if( targetPath[targetPath.size()-1] != '/' ) targetPath = targetPath.substr(0, targetPath.size()-1);

    // Reading the stopwords
    set<string> stopwords = readAllFiles(stopwordsPath);

    // Reading the files
    vector<string> files;
    readFiles(fromPath, files);

    // Read the wordlist
    vector<string> wordlist = readLinesFrom(wordlistPath);

    auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
    cout << "Starting .. " << ctime( &timenow ) << endl;

    // Split the wordlist
    vector< vector<string> > wordListPartitioned = split( wordlist, npartition );
    for( vector<string> &vec : wordListPartitioned ) {

        indexBlock( vec, fromPath, targetPath, files, stopwords );

    }

    return 0;
}