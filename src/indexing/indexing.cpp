#include <iostream>
#include <set>
#include <vector>
#include <filesystem>
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
    cout << "  Indexing FILES=files/ STOPWORDS=stopwords/ WORDLIST=words-file.txt TARGET=index/" << endl;
}

bool createFileIndex( const vector<string> &wordlist, const string &targetPath ) {
    ofstream target( targetPath+string(INDEX_FILENAME), ios::out | ios::binary );
    if( !target ) {
        cout << "Error opening file" << endl; return false;
    }

    for (int i = 0; i < wordlist.size(); i++){
        FixedMKH tmp;
        target.write( (char*) &tmp, sizeof(FixedMKH) );
    }
    target.close();
    return true;
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
        else if( order.rfind("WORDLIST=")==0 ) wordlistPath = order.substr(7);
        else if( order.rfind("TARGET=")==0 ) targetPath = order.substr(7);
    }

    //Verifiying if the paths come with or without the '/' separator
    if( fromPath[fromPath.size()-1] != '/' ) fromPath = fromPath.substr(0, fromPath.size()-1);
    if( stopwordsPath[stopwordsPath.size()-1] != '/' ) stopwordsPath = stopwordsPath.substr(0, stopwordsPath.size()-1);
    if( targetPath[targetPath.size()-1] != '/' ) targetPath = targetPath.substr(0, targetPath.size()-1);

    // Reading the stopwords
    set<string> stopwords = readAllFiles(stopwordsPath);

    // Read the wordlist
    vector<string> wordlist = readUniqueFile(wordlistPath);

    // Creates the file index
    bool successCreated = createFileIndex(wordlist, targetPath);

    // Fill the index
    

    return 0;
}