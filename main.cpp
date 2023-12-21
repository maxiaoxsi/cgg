#include <iostream>
#include<map>
#include "dataExplorer.h"
#include "lexAnalyser.h"
#include "parser.h"

int main(int argc, char **argv) {
    std::cout << "cgg start!" << std::endl;
    std::string fileDir;
    if (argc == 1) {
        fileDir = "testfiles/testfile_yc.txt";
    }
    else if (argc == 2) {
        fileDir = argv[1];
    }
    LexAnalyser testAnalyser(fileDir);
    testAnalyser.analyse();
    Parser testParser;
    testParser.procedure();
    std::cout << "----------------------------------" << std::endl;
    // 打开并保存到文件
    std::ofstream fout("syntaxTree.txt");
    std::string out = "";
    root.printTree(0, false, out);
    fout << out;
    fout.close();
    std::cout << "----------------------------------" << std::endl;
    std::cout << "cgg end!" << std::endl;
    return 0;
}
