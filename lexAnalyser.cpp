//
// Created by maxiaoxsi on 2023/11/10.
//

#include<iostream>
#include<fstream>
#include<map>

#define MAXLINE 1024
#define IS_IDENFR	1
#define IS_NUMBER	2
#define IS_CHAR		3
#define IS_STRING	4
#define IS_OPERATOR	5
#define IS_COMPARE	6
#define IS_BRAKET   7
#define IS_ASSIGN   8
#define IS_COMMA    9
#define IS_SEMICN   10

std::map<std::string, std::string> TKs= {{"const", "CONSTTK"}, {"int", "INTTK"} , {"char", "CHARTK"},
                                         {"void", "VOIDTK"}, {"main", "MAINTK"}, {"if", "IFTK"}, {"else", "ELSETK"},
                                         {"do", "DOTK"}, {"while", "WHILETK"}, {"for", "FORTK"}, {"scanf", "SCANFTK"},
                                         {"print", "PRINTTK"}, {"return", "RETURNTK"}, {"func", "FUNCTIONTK"}};

std::map<std::string, std::string> OPERATORs = { {"+", "PLUS"}, {"-", "MINU"}, {"*", "MULT"}, {"/", "DIV"} };

std::map<std::string, std::string> COMPAREs = { {"<", "LSS"} , {"<=", "LEQ"} , {">", "GRE"} ,
                                                {">=", "GEQ"} , {"==", "EQL"} , {"!=", "NEQ"} };

std::map<std::string, std::string> BRAKETs = { {"(", "LPARENT"} , {")", "RPARENT"} , {"[", "LBRACK"} ,
                                               {"]", "RBRACK"} , {"{", "LBRACE"} , {"}", "RBRACE"} };

class LexAnalyser
{
public:
    explicit LexAnalyser(const std::string& file) {
        fileDir = file;
        std::cout << "test test" << std::endl;
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
