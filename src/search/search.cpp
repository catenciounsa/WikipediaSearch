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

/**
 * @brief Calculates the intersecion of two vectors. Runs on linear time
 * 
 * @param v1 must be in increasing 
 * @param v2 must be in increasing
 * @return vector<int> the intersection of both sets
 */
vector<int> intersection(const vector<int> &v1, const vector<int> &v2) {
    vector<int> ans;
    int i=0,j=0;
    while( i<v1.size() && j<v2.size() ){
        if( v1[i] < v2[j] ) i++;
        else if( v1[i] > v2[j] ) j++;
        else { // match
            ans.push_back( v1[i] );
            i++; j++;
        }
    }
    return ans;
}

vector<int> booleanRetrieval(const vector< vector<int> > &fileIdsPerWord) {
    vector<int> ans = fileIdsPerWord[0];
    for(int i=1; i<fileIdsPerWord.size(); i++){
        ans = intersection( ans, fileIdsPerWord[i] );
        if( ans.size() == 0 ) break;
    }

    return ans;
}

void searchWords( const vector<string> &words,
                  map<string,int> &wordIndex,
                  fstream &index ){

    vector< vector<int> > fileIds;
    for( const string &word : words ) {
        int wordId = wordIndex[word];
        index.seekg( wordId * sizeof(MaxKHeap) );

        // Retrieval from index
        //FixedMKH kheap;
        OptimizedMaxKHeap kheap;
        index.read( (char*) &kheap, sizeof(MaxKHeap) );        

        vector<int> keys = kheap.getKeys(); // Optimization point
        sort(keys.begin(), keys.end());     // sort the values before store them
        fileIds.push_back( keys );
    }
    vector<int> queryResult = booleanRetrieval( fileIds );
    if( queryResult.empty() ) {
        cout << "Sorry, there is no file containing your phrase" << endl;
    } else {
        cout << "The following files contains your answer" << endl;
        int maxQueryResult = 10;
        for( int fileId : queryResult ) {
            cout << fileId << endl;

            if( --maxQueryResult <= 0 ) {
                cout << "and more" << endl;
                return;
            }
        }
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
        vector<string> words1  = getAllWords(query);
        if( words1.size() >  0 ){ //First filter (syntax)
            vector<string> words2;
            for( const string &word : words1) {
                if( (stopwords.count(word) == 0) && !isStopWord(word) )
                    words2.push_back( word );
            }
            if( words2.size() > 0) { //Second filter (stopwords)
                searchWords( words2, wordIndex, index );
            } else {
                cout << "Sorry, such words chosen are very common" << endl;
            }

        }
        cout << ">";
    }
    
   return 0;
}