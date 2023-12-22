//
// Created by maxiaoxsi on 2023/12/20.
//
#include "../parser/parser.h"


/*
 * <VarDecl> → <BType> <VarDef> { ',' <VarDef> } ';'
 */
bool Parser::varDeclMidCode(SyntaxNode varDeclNode) {
    // paras to build
    std::string symbolType = "";
    // mes from node
    SyntaxNode bTypeNode = varDeclNode.child(0);
    symbolType = bTypeNode.Con();
    for (int i = 1; i < varDeclNode.size(); i++) {
        SyntaxNode varDefNode = varDeclNode.child(i);
        varDefMidCode(varDefNode, symbolType);
    }
    return true;
}

/*
 * <InitVal> → <Exp> | '{' [ <InitVal> { ',' InitVal } ] '}'
 */
std::string Parser::initValMidCode(SyntaxNode initValNode) {
    SyntaxNode expNode = initValNode.child(0);
    if (expNode.Label() == "<Exp>") {
        return expMidCode(expNode);
    }
    return "";
}

/*
 * <BType> → 'int' | 'char'
 */
std::string Parser::bTypeMidCode(SyntaxNode bTypeNode) {
    return bTypeNode.Con();
}

/*
 * <Block> → '{' { <BlockItem> } '}'
 * blockItemMidCode
 */
bool Parser::blockMidCode(SyntaxNode blockNode) {
    SymbolTable blockTable;
    blockTable.setParent(curSymbolTable);
    curSymbolTable = blockTable;
    for (int i = 0; i < blockNode.size(); i++) {
        SyntaxNode blockItemNode = blockNode.child(i);
        blockItemMidCode(blockItemNode);
    }
    curSymbolTable = curSymbolTable.parentTable();
    return true;
}

/*
 * <BlockItem> → <ConstDecl> | <VarDecl> | <Stmt>
 */
bool Parser::blockItemMidCode(SyntaxNode blockItemNode) {
    SyntaxNode node = blockItemNode.child(0);
    if (node.Label() == "<ConstDecl>") {
        constDeclMidCode(node);
    }
    else if (node.Label() == "<VarDecl>") {
        varDeclMidCode(node);
    }
    else if (node.Label() == "<Stmt>") {
        stmtMidCode(node);
    }
    return false;
}
