//
// Created by maxiaoxsi on 2023/11/10.
//
#ifndef CGG_LEXANALYSER_H
#define CGG_LEXANALYSER_H
#include<iostream>
#include<fstream>
#include<vector>
#include "dataExplorer.h"
#define MAXLINE 1024

class LexAnalyser{
public:
    explicit LexAnalyser(std::string& fileDir);
    void analyse();
private:
    std::string _fileDir;
    std::ifstream _ifs;
    std::ofstream _lexOutfile;
    std::string _token;
    std::string _line;
    typeId _tokenType;
    int _curPos{};
    int _curLine{};
    char _ch{};
    std::vector<std::string> _tokens;
    void getCh();
    void retractCh();
    void catCh();
    int getToken();
    void putToken(typeId type);
    void putToken(const std::string& type, typeId typeEnum);
    void addToken();
    bool isEOF() const;
    bool isBlank() const;
    bool isAlpha() const;
    bool isAlnum() const;
    bool isDigit() const;
    bool isUnarySym() const;
    bool isOperator() const;
    bool isBracket() const;
    bool isSeparator() const;
    bool isAssign() const;
    bool isLss() const;
    bool isGre() const;
    bool isSquo() const;
    bool isDquo() const;
    bool isChar() const;
    bool isStringC() const;
    int getIdentifierSym();
    int getDigitSym();
    int getUnarySym();
    int getLssCompareSym();
    int getGreCompareSym();
    int getAssignSym();
    int getCharSym();
    int getStringSym();
    void clearToken();
    void getReservedType();
};

#endif //CGG_LEXANALYSER_H