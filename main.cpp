#include <iostream>
#include "lexAnalyser.h"

#include<map>

int main(int argc, char **argv) {
    std::cout << isalnum('(') << std::endl;
    std::cout << "awesome brother chao!" << std::endl;
    std::string fileDir;
    if (argc == 1) {
        fileDir = "../testfile.txt";
    }
    else if (argc == 2) {
        fileDir = argv[1];
    }
    LexAnalyser testAnalyser(fileDir);
    testAnalyser.analyse();
    std::cout << "awesome brother chao!" << std::endl;
    return 0;
}
