#include <iostream>
#include <set>
#include "utils/UtilityFiles.h"

using namespace std;

int main() {
    string path = "/home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/NewTrabajoFinal/WikipediaSearch/data/AsciiAbba/";
    std::vector<std::string> files;
    readFiles(path, files);

    cout << "Read files from main.cpp:"  << endl;
    for( const std::string &file : files ){
        cout << file << endl;
    }
    return 0;   
}