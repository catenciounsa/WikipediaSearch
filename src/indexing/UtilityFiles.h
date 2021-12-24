/**
 * @brief This file contains different
 * 
 */

#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <regex>


/**
 * @brief Get the filename in a path
 * 
 * @param path 
 * @return string the filename
 */
std::string getfilename(const std::string &path) {
        int idx = path.rfind('/')+1;
        std::string file = path.substr(idx);
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
void readFiles( const std::string &path,
                                std::vector<std::string> &files
                                  ) {
        for( const auto & entry : fs::directory_ierator(path)){
                if ( entry.is_directory() )
                        readFiles( entry.path(), files );
                else files.push_back( getfilename(entry.path()));
                //else files.push_back( entry.path() );
        }
}


std::regex rgx("[^[:punct:][:space:][:digit:]]+");


/**
 * @brief Get the words from a sentence
 * 
 * @param seq 
 * @return vector<string> 
 */
std::vector<std::string> getAllWords(const std::string &seq) {
    std::vector<std::string> words;

    for( std::sregex_iterator it(seq.begin(), seq.end(),rgx), it_end; it != it_end; it++) {
        std::string data = it->str() ;
        std::transform(data.begin(), data.end(), data.begin(),
            [](unsigned char c){ return std::tolower(c); });
        if( data.size() > 0)
            words.push_back(data);
    }
    return words;
}