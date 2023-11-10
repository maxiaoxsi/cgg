#include <iostream>
#include "lexAnalyser.h"

int main(int argc, char **argv) {
    std::cout << "awesome brother chao!" << std::endl;
    std::string fileDir;
    if (argc == 1) {
        fileDir = "../testfile.txt";
    }
    else if (argc == 2) {
        fileDir = argv[1];
    }
    LexAnalyser test1(fileDir);
    test1.analyse();
    return 0;
}
