//
// Created by 77902 on 2023/11/22.
//

#ifndef CGG_DATAEXPLORER_H
#define CGG_DATAEXPLORER_H

#include <iostream>
#include <vector>

enum typeId {
    CONSTTK, INTTK, CHARTK, VOIDTK, MAINTK, IFTK, ELSETK, DOTK, WHILETK, FORTK, SCANFTK,
    PRINTFTK, RETURNTK, FUNCTK, BREAKTK, CONTINUETK, //tks
    IDENFR, INTCON, CHARCON, STRCON,
    PLUS, MINU, MULT, DIV, MOD,// operators
    LSS, LEQ, GRE, GEQ, EQL, NEQ, // compares
    OR, AND, NOT, // logic ops
    ASSIGN, SEMICN, COMMA,
    LPARENT, RPARENT, LBRACK, RBRACK, LBRACE, RBRACE //brackets
};

class LexToken {
public:
    LexToken(typeId typeEnum, const std::string &typeStr, const std::string &tokenCon, int line);
    LexToken();
    void println();
    std::string typeStr();
    std::string tokenCon();
    bool isLParent();
    bool isRParent();
    bool isLBrack();
    bool isRBrack();
    bool isLBrace();
    bool isRBrace();
    bool isComma();
    bool isSemicn();
    bool isEql();
    bool isNeq();
    bool isAssign();
    bool isIntTk();
    bool isCharTk();
    bool isBType();
    bool isIdenfr();
    bool isConstTk();
    bool isFuncTk();
    bool isPlus();
    bool isMinu();
    bool isAdd();
    bool isMult();
    bool isDiv();
    bool isMod();
    bool isMul();
    bool isUnaryOp();
    bool isIntCon();
    bool isCharCon();
    bool isNumber();
    bool isMainTk();
    bool isIfTk();
    bool isWhileTk();
    bool isBreakTk();
    bool isContinueTk();
    bool isReturnTk();
    bool isPrintfTk();
    bool isScanfTk();
    bool isElseTk();
    bool isStrCon();
    bool isNot();
    bool isOr();
    bool isAnd();
    bool isLss();
    bool isLeq();
    bool isGre();
    bool isGeq();
    typeId typeEnum();

private:
    std::string _tokenCon;
    std::string _typeStr;
    typeId _typeEnum;
    int _line;
};

class SyntaxNode {
public:
    explicit SyntaxNode(std::string label);
    SyntaxNode();
    void addChild(SyntaxNode child);
    void printTree();
    void setCon(std::string con);
    void println();
    bool isNull();
private:
    std::string _label;
    std::string _con;
    std::vector<SyntaxNode> _children;
};

extern std::vector<LexToken> tokenList;

extern SyntaxNode root;

#endif //CGG_DATAEXPLORER_H
