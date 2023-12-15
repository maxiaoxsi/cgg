//
// Created by 77902 on 2023/11/21.
//

#ifndef CGG_PARSER_H
#define CGG_PARSER_H

#include "dataExplorer.h"

class Parser {
public:
    Parser();
    bool procedure();

private:
    SyntaxNode isConstDecl(bool isGlobal);
    SyntaxNode isVarDecl(bool isGlobal);
    SyntaxNode isFuncDef();
    SyntaxNode isConstDef();
    SyntaxNode isConstInitVal();
    SyntaxNode isVarDef();
    SyntaxNode isIdent();
    SyntaxNode isInitVal();
    SyntaxNode isConstExp();
    SyntaxNode isAddExp();
    SyntaxNode isMulExp();
    SyntaxNode isUnaryExp();
    SyntaxNode isBType();
    SyntaxNode isUnaryOp();
    SyntaxNode isPrimaryExp();
    SyntaxNode isExp();
    SyntaxNode isNumber();
    SyntaxNode isIntConst();
    SyntaxNode isCharConst();
    SyntaxNode isLVal();
    SyntaxNode isFuncRParams();
    SyntaxNode isFuncFParams();
    SyntaxNode isFuncFParam();
    SyntaxNode isFuncFVarParam();
    SyntaxNode isFuncFArrayParam();
    SyntaxNode isFuncFFuncParam();
    SyntaxNode isFuncType();
    SyntaxNode isBlock();
    SyntaxNode isBlockItem();
    SyntaxNode isStmt();
    SyntaxNode isIfStmt();
    SyntaxNode isWhileStmt();
    SyntaxNode isBreakStmt();
    SyntaxNode isContinueStmt();
    SyntaxNode isCond();
    bool isSemicn();
    bool isLParent();
    bool isRParent();
    bool isLBrack();
    bool isRBrack();
    bool isLBrace();
    bool isRBrace();
    bool isFuncTk();
    bool isIfTk();
    bool isElseTk();
    bool isWhileTk();
    bool isBreakTk();
    bool isContinueTk();
    bool setIdx(int idx);
    int _idx;
    LexToken _token;
};


#endif //CGG_PARSER_H
