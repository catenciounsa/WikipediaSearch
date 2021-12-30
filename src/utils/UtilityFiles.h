/**
 * @file UtilityFiles.h
 * @author Carlos E. Atencio-Torres (catencio@unsa.edu.pe)
 * @brief 
 * @version 0.1
 * @date Dic 2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <regex>
#include <filesystem>

using namespace std;
namespace fs = filesystem;


/**
 * @brief Get the filename in a path
 * 
 * @param path 
 * @return string the filename
 */
string getfilename(const string &path) {
        int idx = path.rfind('/')+1;
        string file = path.substr(idx);
        //replaceAll(file," ", "\\ ");
        //replaceAll(file,"(", "\\(");
        //replaceAll(file,")", "\\)");
        return file;
}

/**
 * @brief Reads the file contained in a folder
 * 
 * @param path - folder path
 * @param files - a vector where tu put the files' name.
 */
void readFiles( const string &path,
                                vector<string> &files
                                  ) {
        for( const auto & entry : (fs::directory_iterator(path))){
                if ( entry.is_directory() )
                        readFiles( entry.path(), files );
                else files.push_back( getfilename(entry.path()));
                //else files.push_back( entry.path() );
        }
}


regex rgx("[^[:punct:][:space:][:digit:]]+");


/**
 * @brief Get the words from a sentence
 * 
 * @param seq 
 * @return vector<string> 
 */
vector<string> getAllWords(const string &seq) {
    vector<string> words;

    for( sregex_iterator it(seq.begin(), seq.end(),rgx), it_end; it != it_end; it++) {
        string data = it->str() ;
        transform(data.begin(), data.end(), data.begin(),
            [](unsigned char c){ return tolower(c); });
        if( data.size() > 0)
            words.push_back(data);
    }
    return words;
}

/**
 * @brief Reads all the lines from a file
 * 
 * @param filepath 
 * @return vector<string> 
 */
vector<string> readLinesFrom(const string &filepath) {
        vector<string> lines;
        
        ifstream file(filepath);
        string line;
        while( getline(file, line) ) {
                lines.push_back( line );
        }
        return lines;
}

/**
 * @brief Reads all the files in a folder and returns the list of lines. 
 *        Very util for stopwords list.
 * 
 * @param fromPath 
 * @return vector<string> 
 */
set<string> readAllFiles( const string fromPath ) {
    set<string> lines;

    vector< string > files;
    readFiles( fromPath, files );

    for( const string &fileName : files ){
        vector<string> linesFromFile = readLinesFrom( fromPath + fileName );
        for( string line : linesFromFile ) {
                lines.insert( line );
        }
    }
    return lines;
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

map<string, int> transformIntoIndex(const string &filepath) {
    map<string,int> wordIndex;
    vector<string> lines = readLinesFrom(filepath);
    for(int i=0; i<lines.size(); i++ ){
        wordIndex[lines[i]] = i;
    }
    return wordIndex;
}


vector< vector<string> > split( vector<string> &entries, int partition){
    vector< vector<string> > ans; 
    int sizePartition = entries.size() / partition;
    int idx = 0;

    while((--partition) > 0 ) { //it executes partition - 1 times
        vector<string> chunk( entries.begin() + idx, entries.begin() + idx + sizePartition );
        ans.push_back( chunk );
        idx += sizePartition;
    }
    if( idx < entries.size() ) {
        vector<string> chunk( entries.begin()+ idx, entries.end() );
        ans.push_back( chunk );
    }
    return ans;
}

string numberWithZeros( int val, int filenameSize ) {
    char format[16], strval[16];
    sprintf(format, "%%0%dd", filenameSize);
    sprintf(strval,  format, val );
    return string(strval);
}


