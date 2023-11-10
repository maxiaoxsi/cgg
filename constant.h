//
// Created by maxiaoxsi on 2023/11/10.
//

#ifndef CGG_CONSTANT_H
#define CGG_CONSTANT_H
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


std::string TKs[14][2] = { {"const", "CONSTTK"}, {"int", "INTTK"} , {"char", "CHARTK"},
                      {"void", "VOIDTK"}, {"main", "MAINTK"}, {"if", "IFTK"}, {"else", "ELSETK"},
                      {"do", "DOTK"}, {"while", "WHILETK"}, {"for", "FORTK"}, {"scanf", "SCANFTK"},
                      {"print", "PRINTTK"}, {"return", "RETURNTK"}, {"func", "FUNCTIONTK"} };

std::string OPERATORs[4][2] = { {"+", "PLUS"}, {"-", "MINU"}, {"*", "MULT"}, {"/", "DIV"} };

std::string COMPAREs[6][2] = { {"<", "LSS"} , {"<=", "LEQ"} , {">", "GRE"} ,
                          {">=", "GEQ"} , {"==", "EQL"} , {"!=", "NEQ"} };

std::string BRAKETs[6][2] = { {"(", "LPARENT"} , {")", "RPARENT"} , {"[", "LBRACK"} ,
                         {"]", "RBRACK"} , {"{", "LBRACE"} , {"}", "RBRACE"} };

#endif