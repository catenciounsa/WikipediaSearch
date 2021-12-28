#include <iostream>
#include <vector>
#include <set>
#include "UtilityFiles.h"

using namespace std;

void welcomeWordsScriptMessage() {
    std::cout << "***************************************" << std::endl;
    std::cout << "Welcome to WikipediaSearch " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "This script reads the files from a folder" << std::endl;
    std::cout << "It creates a file with the chosen words" << std::endl;
    std::cout << "***************************************" << std::endl;
}

void instructionMessage() {
    std::cout << "USAGE: Words <params> " << std::endl;
    std::cout << "PARAMS:" << std::endl;
    std::cout << "  FILES=/path/from/files/" << std::endl;
    std::cout << "  STOPWORDS=/path/to/stopwords/" << std::endl;
    std::cout << "  TARGET=/path/to/words-file"<< std::endl;
    std::cout << "EXAMPLE:" << std::endl;
    std::cout << "  Words FILES=files/ STOPWORDS=stopwords/ TARGET=words-file.txt" << std::endl;
}

/**
 * @brief This function verifies simple rules to verify if a word is candidate of stopword
 * 
 * @param word 
 * @return true 
 * @return false 
 */
bool isStopWord(const std::string &word) {
    if( word.size() < 4 ) return true;
    
    // The follow rule verifies errors like 'ooooohhhhshhhh'
    // It is commented because of its computational cost.
    // If it is applied to all the words on Wikipedia, probably 
    // will take x10 times the time normally required.
    /*
    std::set<char> freq;
    for( char c : word ) freq.insert(c);
    if( freq.size() < (word.size()/3) ) return true;
    */

    return false;
}

std::set<std::string> getStopWords(const std::string &stopwordsPath) {
    std::set<std::string> stopwords;

    std::vector< std::string > files;
    readFiles( stopwordsPath, files );

    for( const std::string &fileName : files ){
        ifstream file(stopwordsPath + fileName);

        string line;
        while( getline(file, line) ) {
            stopwords.insert( line );
        }
    }
    return stopwords;
}

std::set<std::string> getUniqueWords(   const std::string &fromPath,
                                        const set<std::string> &stopwords
                                        ) {
    std::set<std::string> unique_words;
    std::vector< std::string > files;

    readFiles( fromPath, files );

    int nFiles = 1;
    int jump = files.size() / 10;
    int percentage = 10;

    std::string line;
    for( const std::string &fileName : files ){
        ifstream file(fromPath + fileName);
        if( ((nFiles++) % jump) == 0 ) {
            if( percentage >= 100 ) break;
            std::cout << percentage << "%: " << nFiles << " proceseed" << std::endl;
            percentage += 10;
        }
        while( std::getline(file, line) ) {
            for( string word : getAllWords(line) ) {
                if( stopwords.count(word) == 0 && !isStopWord(word) ) {
                    unique_words.insert( word ) ;
                }
            }
        }
    }
    cout << "Proceseed 100% " << files.size() << endl;
    return unique_words;
}

int main(int argc, char **argv) {
    welcomeWordsScriptMessage();
    if( argc != 4 ) {
        instructionMessage();
        return 0;
    }

    // Reading the parameters
    std::string fromPath, stopwordsPath, targetPath;
    
    for(int i=1; i<argc; i++){
        string order = string( argv[i] );
        if( order.rfind("FILES=")==0 ) fromPath = order.substr(6);
        else if( order.rfind("STOPWORDS=")==0 )  stopwordsPath = order.substr(10);
        else if( order.rfind("TARGET=")==0 ) targetPath = order.substr(7);
    }

    //Verifiying if the paths come with or without the '/' separator

    if( fromPath[fromPath.size()-1] != '/' ) fromPath = fromPath.substr(0, fromPath.size()-1);
    if( stopwordsPath[stopwordsPath.size()-1] != '/' ) stopwordsPath = stopwordsPath.substr(0, stopwordsPath.size()-1);

    
    // Reading the stopwords
    std::set<std::string> stopwords = getStopWords(stopwordsPath);

    // Get the unique words from files in 'fromPath'
    std::set<std::string> uniquewords = getUniqueWords(fromPath, stopwords );
    
    // Recording the list of words
    ofstream fileout(targetPath);
    for( std::string word : uniquewords )
        fileout << word << endl;
    fileout.close();
    std::cout << std::endl;
    std::cout << "The words file was succesfuly created: " << std::endl;
    std::cout << "   " << targetPath << std::endl;
    std::cout << "***************************************" << std::endl;
    
    return 0;   
}