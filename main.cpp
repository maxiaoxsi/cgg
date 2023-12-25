#include <iostream>
#include<map>
#include "dataExplorer/dataExplorer.h"
#include "lex/lexAnalyser.h"
#include "parser/parser.h"

void printMidCode() {
    for (int i = 0; i < midCodeList.size(); i++) {
        midCodeList[i].println();
    }
}

int main(int argc, char **argv) {
    std::cout << "cgg start!" << std::endl;
    std::string fileDir;
    if (argc == 1) {
        fileDir = "../testfile.txt";
    }
    else if (argc == 2) {
        fileDir = argv[1];
    }
    LexAnalyser testAnalyser(fileDir);
    testAnalyser.analyse();
    Parser testParser;
    testParser.procedure();
    std::cout << "-----------------SyntaxTree----------------------" << std::endl;
    std::ofstream fout("syntaxTree.txt");
    std::string out = "";
    root.printTree(0, false, out);
    fout << out;
    fout.close();
    std::cout << "----------------------------------" << std::endl;
    std::cout << "cgg end!" << std::endl;
    /*
    std::cout << "-----------------MidCode-------------------------" << std::endl;
    printMidCode();
    */
    return 0;
}
