//
// Created by maxiaoxsi on 2023/11/21.
//

#ifndef CGG_PARSER_H
#define CGG_PARSER_H

#include "../dataExplorer/dataExplorer.h"

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
    SyntaxNode isAddOp();
    SyntaxNode isMulOp();
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
    SyntaxNode isReturnStmt();
    SyntaxNode isAssignStmt();
    SyntaxNode isPrintfStmt();
    SyntaxNode isScanfStmt();
    SyntaxNode isFormatString();
    SyntaxNode isCond();
    SyntaxNode isLOrExp();
    SyntaxNode isLAndExp();
    SyntaxNode isEqExp();
    SyntaxNode isRelExp();
    SyntaxNode isMainFuncDef();
    SyntaxNode isThreadFuncDef();
    bool isComma();
    bool isSemicn();
    bool isAssign();
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
    bool isPrintfTk();
    bool isScanfTk();
    bool isIntTk();
    bool isMainTk();
    bool isConstTk();
    bool isReturnTk();
    bool isThreadTk();
    bool isStrCon();
    bool isEql();
    bool isNeq();
    bool isLss();
    bool isLeq();
    bool isGre();
    bool isGeq();
    bool isAdd();
    bool isMul();
    bool setIdx(int idx);
    bool constDeclMidCode(SyntaxNode constDeclNode);
    std::string constInitValMidCode(SyntaxNode constInitValNode);
    std::string constExpMidCode(SyntaxNode constExpNode);
    bool constDefMidCode(SyntaxNode constDefNode, std::string type);
    bool varDeclMidCode(SyntaxNode varDeclNode);
    bool funcDefMidCode(SyntaxNode funcDefNode);
    bool mainFuncDefMidCode(SyntaxNode mainFuncDefNode);
    bool funcFParamsMidCode(SyntaxNode funcFParamsNode);
    bool funFParamMidCode(SyntaxNode funcFParamNode);
    bool funcRParamsMidCode(SyntaxNode funcRParamsNode);
    bool blockMidCode(SyntaxNode blockNode);
    bool blockItemMidCode(SyntaxNode blockItemNode);
    bool stmtMidCode(SyntaxNode stmtMidCode);
    bool assignStmtMidCode(SyntaxNode assignStmtNode);
    bool returnStmtMidCode(SyntaxNode returnStmtNode);
    bool printfStmtMidCode(SyntaxNode printfStmtNode);
    std::string formatStringMidCode(SyntaxNode formatStringNode);
    std::string initValMidCode(SyntaxNode initValNode);
    std::string expMidCode(SyntaxNode expNode);
    std::string addExpMidCode(SyntaxNode addExpNode);
    std::string mulExpMidCode(SyntaxNode mulExpNode);
    std::string unaryExpMidCode(SyntaxNode unaryExpNode);
    std::string primaryExpMidCode(SyntaxNode primaryExpNode);
    std::string lValMidCode(SyntaxNode lValNode);
    std::string lValIdentMidCode(SyntaxNode lValNode);
    std::string lValIdxMidCode(SyntaxNode lValNode);
    std::string identMidCode(SyntaxNode identNode);
    std::string numberMidCode(SyntaxNode numberNode);
    std::string funcTypeMidCode(SyntaxNode funcTypeNode);
    std::string bTypeMidCode(SyntaxNode bTypeNode);
    std::string funcFVarParamMidCode(SyntaxNode funcFVarParamNode);
    operation addOpMidCode(SyntaxNode addOpNode);
    operation mulOpMidCode(SyntaxNode mulOpNode);
    operation unaryOpMidCode(SyntaxNode unaryOpNode);
    bool varDefMidCode(SyntaxNode varDefNode, std::string type);
    //bool funcDefMidCode(SyntaxNode funcDefNode);
    int _idx;
    LexToken _token;
    SymbolTable curSymbolTable;
    TempVarPool _tempPool;
};


#endif //CGG_PARSER_H
