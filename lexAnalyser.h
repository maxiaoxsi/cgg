//
// Created by maxiaoxsi on 2023/11/10.
//
#include<map>

#ifndef CGG_LEXANALYSER_H
#define CGG_LEXANALYSER_H

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

class LexAnalyser{
public:
    explicit LexAnalyser(const std::string& file) {}
    void analyse() {}
};

#endif