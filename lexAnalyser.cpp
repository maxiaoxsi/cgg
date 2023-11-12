//
// Created by maxiaoxsi on 2023/11/10.
//

#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include "lexAnalyser.h"

std::map<std::string, std::string> TKs= {{"const", "CONSTTK"}, {"int", "INTTK"} , {"char", "CHARTK"},
                                         {"void", "VOIDTK"}, {"main", "MAINTK"}, {"if", "IFTK"}, {"else", "ELSETK"},
                                         {"do", "DOTK"}, {"while", "WHILETK"}, {"for", "FORTK"}, {"scanf", "SCANFTK"},
                                         {"print", "PRINTTK"}, {"return", "RETURNTK"}, {"func", "FUNCTIONTK"}};

std::map<std::string, std::string> OPERATORs = { {"+", "PLUS"}, {"-", "MINU"}, {"*", "MULT"}, {"/", "DIV"} };

std::map<std::string, std::string> COMPAREs = { {"<", "LSS"} , {"<=", "LEQ"} , {">", "GRE"} ,
                                                {">=", "GEQ"} , {"==", "EQL"} , {"!=", "NEQ"} };

std::map<std::string, std::string> BRAKETs = { {"(", "LPARENT"} , {")", "RPARENT"} , {"[", "LBRACK"} ,
                                               {"]", "RBRACK"} , {"{", "LBRACE"} , {"}", "RBRACE"} };


LexAnalyser::LexAnalyser(std::string &file) {
    fileDir = file;
    std::cout << file << std::endl;
}

void LexAnalyser::analyse() {
    ifs.open(fileDir, std::ios::in);
    if (!ifs.is_open()) {
        std::cout << "fail to open!\n";
        perror("fail to open!\n");
        return;
    }
    int to;
    while((to = getToken()) != -1) {
        std::cout << "to=" << to << ", token=" << token << std::endl;
    }
}

int LexAnalyser::getToken() {
    return 0;
}

bool LexAnalyser::isBlank() {
    return (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == '\f' || ch == '\v');
}

void LexAnalyser::getCh() {

}
