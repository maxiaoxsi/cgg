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
 * <VarDef> → <Ident> { '[' <ConstExp> ']' } [ '=' <InitVal> ]
 */
bool Parser::varDefMidCode(SyntaxNode varDefNode, std::string type) {
    std::string symbolName = "";
    int symbolAddr = -1;
    std::string symbolKind = "VAR";
    std::string symbolType = type;
    int symbolConstInt = -1;
    char symbolConstChar = -1;
    std::vector<int> symbolLength = {};
    operation op = VAR;
    // mes from node
    SyntaxNode identNode = varDefNode.child(0);
    symbolName = identNode.Con();
    int size = 1;
    for (int i = 1; i < varDefNode.size() && varDefNode.child(i).Label() == "<ConstExp>"; i++) {
        symbolKind = "ARRAY";
        op = ARRAY;
        SyntaxNode constExpNode = varDefNode.child(i);
        int constNum = constExpNode.constNumber();
        symbolLength.push_back(constNum);
        size = size * constNum;
    }
    SyntaxNode initValNode = varDefNode.child(varDefNode.size() - 1);
    std::string midCodeZ = "";
    if (symbolType == "ARRAY") {
        midCodeZ = std::to_string(size);
    }
    if(initValNode.Label() == "<InitVal>") {
        midCodeZ = initValMidCode(initValNode);
    }
    curSymbolTable.addItem(symbolName, symbolAddr, symbolKind,symbolType,
                           symbolConstInt, symbolConstChar, symbolLength);
    midCodeList.push_back(MidCode(op, symbolType, symbolName, midCodeZ));
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
