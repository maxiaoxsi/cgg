//
// Created by maxiaoxsi on 2023/12/21.
//

#include "../parser/parser.h"

/*
 * <ConstDecl> → ‘const’ <BType> <ConstDef> {‘,’ <ConstDef>} ';'
 * constDefMidCode
 */
bool Parser::constDeclMidCode(SyntaxNode constDeclNode) {
    // paras to build
    std::string symbolType = "";
    // mes from node
    SyntaxNode bTypeNode = constDeclNode.child(0);
    symbolType = bTypeNode.Con();
    for (int i = 1; i < constDeclNode.size(); i++) {
        SyntaxNode constDefNode = constDeclNode.child(i);
        constDefMidCode(constDefNode, symbolType);
    }
    return true;
}

/*
 * <ConstDef> → <Ident> '=' <ConstInitVal>
 * CONST identCon constexp constinitval
 */
bool Parser::constDefMidCode(SyntaxNode constDefNode, std::string type) {
    // paras to build
    std::string symbolName = "";
    int symbolAddr = -1;
    std::string symbolKind = "CONST";
    std::string symbolType = type;
    int symbolConstInt = -1;
    char symbolConstChar = -1;
    std::vector<int> symbolLength = {};
    operation constOp = CONST;
    // mes from node
    SyntaxNode identNode = constDefNode.child(0);
    symbolName = identNode.Con();
    std::string midCodeY = "0";
    if (constDefNode.size() == 2) {
        SyntaxNode constInitValNode = constDefNode.child(1);
        midCodeY = constInitValMidCode(constInitValNode);
    }
    curSymbolTable.addItem(symbolName, symbolAddr, symbolKind,symbolType,
                           symbolConstInt, symbolConstChar, symbolLength);
    midCodeList.push_back(MidCode(constOp, symbolName, symbolType, midCodeY));
    return true;
}

/*
 * <ConstInitVal> → <ConstExp>
 * constExpMidCode
 */
std::string Parser::constInitValMidCode(SyntaxNode constInitValNode) {
    SyntaxNode constExpNode = constInitValNode.child(0);
    return constExpMidCode(constExpNode);
}

/*
 * <ConstExp> → <AddExp>
 */
std::string Parser::constExpMidCode(SyntaxNode constExpNode) {
    SyntaxNode addExpNode = constExpNode.child(0);
    std::string expZ = addExpMidCode(addExpNode);
    return expZ;
}