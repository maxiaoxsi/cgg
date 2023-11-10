//
// Created by maxiaoxsi on 2023/11/10.
//

#ifndef CGG_LEXANALYSER_H
#define CGG_LEXANALYSER_H

#include<iostream>
#include<fstream>

class LexAnalyser
{
public:
    explicit LexAnalyser(const std::string& file) {
        fileDir = file;
        std::cout << file << std::endl;
    }

    void analyse() {
        ifs.open(fileDir, std::ios::in);
        if (!ifs.is_open()) {
            std::cout << "fail to open" << std::endl;
            perror("fail to read");
            return;
        }
        int a;
        while((a = getword()) != -1) {
            std::cout << "a=" << a << ", word=" << word << std::endl;
        }
    }

private:
    std::string fileDir;
    std::ifstream ifs;
    std::string word;
    char c;
    int getword() {
        word = "";
        ifs.get(c);
        while (c == ' ' || c == '   ' || c == '\n') {
            ifs.get(c);
        }
        if (c == EOF) {
            return -1;
        }
        if (isalpha(c) || c == '_') {
            while ( c == '_' || isalnum(c)) {
                word += c;
                ifs.get(c);
            }
            std:: cout << c << std::endl;
            ifs.seekg(-1, ifs.cur);
            c = ifs.get();
            std::cout << c << std::endl;

            return IS_IDENFR;
        }
        if (isdigit(c)) {
            while (isdigit(c)) {
                word += c;
                ifs.get(c);
            }
            ifs.seekg(-1, ifs.cur);
            return IS_NUMBER;
        }
        if ( c == '+' || c == '-' || c == '*' || c == '/') {
            word += c;
            return IS_OPERATOR;
        }
        if ( c == '(' || c == ')' || c == '(' || c == '[' || c == ']' || c == '{' || c == '}') {
            word += c;
            return IS_BRAKET;
        }
        if (c == ',') {
            word += c;
            return IS_COMMA;
        }
        if (c == ';') {
            word += c;
            return IS_SEMICN;
        }
        if ( c == '<' || c == '>') {
            word += c;
            ifs.get(c);
            if ( c == '=') {
                word += c;
                return IS_COMPARE;
            }
            else {
                ifs.seekg(-1, ifs.cur);
                return IS_COMPARE;
            }
        }
        if (c == '=') {
            word += c;
            ifs.get(c);
            if (c == '=') {
                word += c;
                return IS_COMPARE;
            }
            else {
                ifs.seekg(-1, ifs.cur);
                return IS_ASSIGN;
            }
        }
        if (c == '!') {
            word += c;
            ifs.get(c);
            if (c == '=') {
                word += c;
                return IS_COMPARE;
            }
        }
        if (c == '\'') {
            ifs.get(c);
            word += c;
            ifs.get(c);
            if (c == '\'') {
                return IS_CHAR;
            }
        }
        if (c == '\"') {
            ifs.get(c);
            while (c != '\"') {
                word += c;
                ifs.get(c);
            }
            return IS_STRING;
        }
    }
};


#endif