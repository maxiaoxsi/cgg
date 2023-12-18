//
// Created by maxiaoxsi on 2023/11/10.
//

#include<iostream>
#include<map>
#include<cctype>
#include<sstream>
#include "lexAnalyser.h"
#include "dataExplorer.h"

enum typeId _tokenType;

std::map<std::string, typeId> reservedWordMap =
        {{"const", CONSTTK}, {"int", INTTK}, {"char", CHARTK}, {"void", VOIDTK},
         {"main", MAINTK}, {"if", IFTK}, {"else", ELSETK}, {"do", DOTK},
         {"while", WHILETK}, {"for", FORTK}, {"scanf", SCANFTK},
         {"printf", PRINTFTK}, {"return", RETURNTK}, {"func", FUNCTK},
         {"thread", THREAD}};

std::map<char, typeId> operatorMap =
        {{'+', PLUS}, {'-', MINU}, {'*', MULT}, {'/', DIV} , {'%', MOD}};

std::map<char, typeId> bracketMap =
        {{'(', LPARENT}, {')', RPARENT} ,{'[', LBRACK} ,
         {']', RBRACK}, {'{', LBRACE}, {'}', RBRACE}};

std::map<char, typeId> separatorMap =
        {{',', COMMA}, {';', SEMICN}};

LexAnalyser::LexAnalyser(std::string& fileDir) {
    _fileDir = fileDir;
}

void LexAnalyser::analyse() {
    _ifs.open(_fileDir, std::ios::in);
    if (!_ifs.is_open()) {
        perror("fail to open input file!\n");
        return;
    }
    _lexOutfile.open("lexical.txt");
    if (!_lexOutfile.is_open()) {
        perror("fail to open lexical output file!\n");
    }
    _curPos = 0;
    _curLine = 0;
    while(getToken() != -1) {
        putToken(_tokenType);
    }
}

int LexAnalyser::getToken() {
    clearToken();
    getCh();
    while(isBlank()) {
        getCh();
    }
    if (isEOF()) {
        return -1;
    }
    if (isAlpha()) {
        return getIdentifierSym();
    }
    if (isDigit()) {
        return getDigitSym();
    }
    if (isSquo()) {
        return getCharSym();
    }
    if (isDquo())  {
        return getStringSym();
    }
    if (isUnarySym()) {
        return getUnarySym();
    }
    if (isLss()) {
        return getLssCompareSym();
    }
    if (isGre()) {
        return getGreCompareSym();
    }
    if (isAssign()) {
        return getAssignSym();
    }
    return -1;
}

void LexAnalyser::getCh() {
    if (_curPos >= _line.size()) {
        if (!std::getline(_ifs, _line)) {
            _ch = EOF;
            return;
        }
        _curPos = 0;
        _curLine++;
    }
    _ch = _line[_curPos];
    _curPos++;
}

void LexAnalyser::retractCh() {
    _curPos--;
}

void LexAnalyser::catCh() {
    _token += _ch;
}

void LexAnalyser::clearToken() {
    _token = "";
}

void LexAnalyser::getReservedType() {
    if (reservedWordMap.find(_token) == reservedWordMap.end()) {
        _tokenType = IDENFR;
        return;
    }
    _tokenType = reservedWordMap[_token];
}

bool LexAnalyser::isEOF() const {
    return _ch == EOF;
}

bool LexAnalyser::isBlank() const {
    //return (_ch == ' ' || _ch == '\n' || _ch == '\t' || _ch == '\r' || _ch == '\f' || _ch == '\v');
    return isspace(_ch);
}

bool LexAnalyser::isAlnum() const {
    return (_ch == '_') || isalnum(_ch);
}

bool LexAnalyser::isAlpha() const {
    return (_ch == '_') || isalpha(_ch);
}

bool LexAnalyser::isDigit() const {
    return isdigit(_ch);
}

bool LexAnalyser::isUnarySym() const {
    return isOperator() || isBracket() || isSeparator();
}

bool LexAnalyser::isOperator() const {
    return (_ch == '+') || (_ch == '-') || (_ch == '*') || (_ch == '/');
}

bool LexAnalyser::isBracket() const {
    return  (_ch == '(') || (_ch == ')') || (_ch == '[') ||
            (_ch == ']') || (_ch == '{') || (_ch == '}');
}

bool LexAnalyser::isSeparator() const {
    return (_ch == ',') || (_ch == ';');
}

void LexAnalyser::putToken(typeId type) {
    switch (type) {
        case IDENFR:
            putToken("IDENFR", IDENFR);
            break;
        case INTCON:
            putToken("INTCON", INTCON);
            break;
        case CHARCON:
            putToken("CHARCON", CHARCON);
            break;
        case STRCON:
            putToken("STRCON", STRCON);
            break;
        case CONSTTK:
            putToken("CONSTTK", CONSTTK);
            break;
        case INTTK:
            putToken("INTTK", INTTK);
            break;
        case CHARTK:
            putToken("CHARTK", CHARTK);
            break;
        case VOIDTK:
            putToken("VOIDTK", VOIDTK);
            break;
        case MAINTK:
            putToken("MAINTK", MAINTK);
            break;
        case IFTK:
            putToken("IFTK", IFTK);
            break;
        case ELSETK:
            putToken("ELSETK", ELSETK);
            break;
        case DOTK:
            putToken("DOTK", DOTK);
            break;
        case WHILETK:
            putToken("WHILETK", WHILETK);
            break;
        case FORTK:
            putToken("FORTK", FORTK);
            break;
        case SCANFTK:
            putToken("SCANFTK", SCANFTK);
            break;
        case PRINTFTK:
            putToken("PRINTFTK", PRINTFTK);
            break;
        case RETURNTK:
            putToken("RETURNTK", RETURNTK);
            break;
        case FUNCTK:
            putToken("FUNCTK", FUNCTK);
            break;
        case PLUS:
            putToken("PLUS", PLUS);
            break;
        case MINU:
            putToken("MINU", MINU);
            break;
        case MULT:
            putToken("MULT", MULT);
            break;
        case DIV:
            putToken("DIV", DIV);
            break;
        case LSS:
            putToken("LSS", LSS);
            break;
        case LEQ:
            putToken("LEQ", LEQ);
            break;
        case GRE:
            putToken("GRE", GRE);
            break;
        case GEQ:
            putToken("GEQ", GEQ);
            break;
        case EQL:
            putToken("EQL", EQL);
            break;
        case NEQ:
            putToken("NEQ", NEQ);
            break;
        case ASSIGN:
            putToken("ASSIGN", ASSIGN);
            break;
        case SEMICN:
            putToken("SEMICN", SEMICN);
            break;
        case COMMA:
            putToken("COMMA", COMMA);
            break;
        case LPARENT:
            putToken("LPARENT", LPARENT);
            break;
        case RPARENT:
            putToken("RPARENT", RPARENT);
            break;
        case LBRACK:
            putToken("LBRACK", LBRACK);
            break;
        case RBRACK:
            putToken("RBRACK", RBRACK);
            break;
        case LBRACE:
            putToken("LBRACE", LBRACE);
            break;
        case RBRACE:
            putToken("RBRACE", RBRACE);
            break;
        case THREAD:
            putToken("THREAD", THREAD);
            break;
        default:
            break;
    }
}

void LexAnalyser::putToken(const std::string& typeStr, typeId typeEnum) {
    _lexOutfile << typeStr << " " << _token << std::endl;
    LexToken tempToken(typeEnum, typeStr, _token, _curLine);
    tokenList.push_back(tempToken);
}

bool LexAnalyser::isLss() const {
    return (_ch == '<');
}

bool LexAnalyser::isGre() const {
    return (_ch == '>');
}

bool LexAnalyser::isAssign() const {
    return (_ch == '=');
}

bool LexAnalyser::isSquo() const {
    return _ch == '\'';
}

bool LexAnalyser::isDquo() const {
    return _ch == '\"';
}

bool LexAnalyser::isChar() const {
    return (_ch >= 35 && _ch <= 126) || (_ch == 32) || (_ch == 33);
}

int LexAnalyser::getUnarySym() {
    catCh();
    if (isOperator()) {
        _tokenType = operatorMap[_ch];
        return 0;
    }
    if (isBracket()) {
        _tokenType = bracketMap[_ch];
        return 0;
    }
    if (isSeparator()) {
        _tokenType = separatorMap[_ch];
        return 0;
    }
    return 1;
}

int LexAnalyser::getLssCompareSym() {
    catCh();
    getCh();
    if (isAssign()) {
        catCh();
        _tokenType = LEQ;
    } else {
        retractCh();
        _tokenType = LSS;
    }
    return 0;
}

int LexAnalyser::getGreCompareSym() {
    catCh();
    getCh();
    if (isAssign()) {
        catCh();
        _tokenType = GEQ;
    } else {
        retractCh();
        _tokenType = GRE;
    }
    return 0;
}

int LexAnalyser::getAssignSym() {
    catCh();
    getCh();
    if (isAssign()) {
        catCh();
        _tokenType = EQL;
    } else {
        retractCh();
        _tokenType = ASSIGN;
    }
    return 0;
}

int LexAnalyser::getDigitSym() {
    while (isDigit()) {
        catCh();
        getCh();
    }
    retractCh();
    _tokenType = INTCON;
    return 0;
}

int LexAnalyser::getIdentifierSym() {
    while(isAlnum()) {
        catCh();
        getCh();
    }
    retractCh();
    getReservedType();
    return 0;
}

int LexAnalyser::getCharSym() {
    getCh();
    if (isChar()) {
        char temp = _ch;
        getCh();
        if (isSquo()) {
            _ch = temp;
            catCh();
            _tokenType = CHARCON;
        }
    }
    return 0;
}

bool LexAnalyser::isStringC() const {
    return (_ch >= 35 && _ch <= 126) || (_ch == 32) || (_ch == 33);
}

int LexAnalyser::getStringSym() {
    getCh();
    while (isStringC()) {
        catCh();
        getCh();
    }
    if (isDquo()) {
        _tokenType = STRCON;
    }
    return 0;
}
