#include <iostream>
#include<map>
#include "dataExplorer.h"
#include "lexAnalyser.h"
#include "parser.h"

int main(int argc, char **argv) {
    std::cout << "cgg start!" << std::endl;
    std::string fileDir;
    if (argc == 1) {
        fileDir = "testfile.txt";
    }
    else if (argc == 2) {
        fileDir = argv[1];
    }
    LexAnalyser testAnalyser(fileDir);
    testAnalyser.analyse();
    Parser testParser;
    testParser.procedure();
    std::cout << "----------------------------------" << std::endl;
    root.printTree();
    return 0;
}
