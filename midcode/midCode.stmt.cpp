//
// Created by maxiaoxsi on 2023/12/20.
//

#include "../parser/parser.h"

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
    }
    return true;
}
