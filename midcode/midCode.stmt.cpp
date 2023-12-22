//
// Created by maxiaoxsi on 2023/12/20.
//

#include "../parser/parser.h"

/*
 * <Stmt> → <AssignStmt> | [<Exp>] ';' | <Block> | <IfStmt> | <WhileStmt> | <BreakStmt> | <ContinueStmt>
 * | <ReturnStmt> | <PrintfStmt> | <ScanfStmt>
 */
bool Parser::stmtMidCode(SyntaxNode stmtMidCode) {
    if (stmtMidCode.size() == 0) {
        return true;
    }
    SyntaxNode node = stmtMidCode.child(0);
    if (node.Label() == "<AssignStmt>") {
        assignStmtMidCode(node);
    }
    else if (node.Label() == "<Exp>") {
        expMidCode(node);
    }
    else if (node.Label() == "<Block>") {
        blockMidCode(node);
    }
    else if (node.Label() == "<IfStmt>") {
        //ifStmtMidCode(node);
    }
    else if (node.Label() == "<WhileStmt>") {
        //whileStmtMidCode(node);
    }
    else if (node.Label() == "<BreakStmt>") {
        //breakStmtMidCode(node);
    }
    else if (node.Label() == "<ContinueStmt>") {
        //continueStmtMidCode(node);
    }
    else if (node.Label() == "<ReturnStmt>") {
        returnStmtMidCode(node);
    }
    else if (node.Label() == "<PrintfStmt>") {
        //printfStmtMidCode(node);
    }
    else if (node.Label() == "<ScanfStmt>") {
        //scanfStmtMidCode(node);
    }
    return true;
}

/*
 * <AssignStmt> → <LVal> '=' <Exp> ';'
 */
bool Parser::assignStmtMidCode(SyntaxNode assignStmtNode) {
    SyntaxNode lValNode = assignStmtNode.child(0);
    SyntaxNode expNode = assignStmtNode.child(1);
    if (lValNode.size() == 1) {
        std::string assignZ = lValIdentMidCode(lValNode);
        std::string assignX = expMidCode(expNode);
        midCodeList.push_back(MidCode(ASSIGNOP, assignZ, assignX, ""));
        if (assignX[0] == '~') {
            _tempPool.freeTempVar(assignX);
        }
    }
    else {
        std::string putarrayZ = lValIdentMidCode(lValNode);
        std::string putarrayX = lValIdxMidCode(lValNode);
        std::string putarrayY = expMidCode(expNode);
        midCodeList.push_back(MidCode(PUTARRAY, putarrayZ, putarrayX, putarrayY));
        if (putarrayX[0] == '~') {
            _tempPool.freeTempVar(putarrayX);
        }
        if (putarrayY[0] == '~') {
            _tempPool.freeTempVar(putarrayY);
        }
    }
    return true;
}

/*
 * <ReturnStmt> → 'return' [Exp] ';'
 */
bool Parser::returnStmtMidCode(SyntaxNode returnStmtNode) {
    if (returnStmtNode.size() == 0) {
        midCodeList.push_back(MidCode(RET, "0", "", ""));
    }
    else {
        SyntaxNode expNode = returnStmtNode.child(0);
        std::string retZ = expMidCode(expNode);
        midCodeList.push_back(MidCode(RET, retZ, "", ""));
        if (retZ[0] == '~') {
            _tempPool.freeTempVar(retZ);
        }
    }
    return true;
}
