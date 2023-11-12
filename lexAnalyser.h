//
// Created by maxiaoxsi on 2023/11/10.
//
#ifndef CGG_LEXANALYSER_H
#define CGG_LEXANALYSER_H

#include<iostream>
#include<fstream>
#define MAXLINE 1024

class LexAnalyser{
public:
    explicit LexAnalyser(std::string& file);
    void analyse();
private:
    std::string fileDir;
    std::ifstream ifs;
    std::string token;
    char ch;
    void getCh();
    int getToken();
    bool isBlank();
};

#endif