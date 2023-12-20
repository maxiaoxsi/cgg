//
// Created by MXX on 2023/12/20.
//
#include "../parser/parser.h"

/*
 * <ConstDecl> → ‘const’ <BType> <ConstDef> {‘,’ <ConstDef>} ';'
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
 * <ConstDef> → <Ident> { '[' <ConstExp> ']' } '=' <ConstInitVal>
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
    operation op = CONST;
    // mes from node
    SyntaxNode identNode = constDefNode.child(0);
    symbolName = identNode.Con();
    int size = 1;
    for (int i = 1; i < constDefNode.size() && constDefNode.child(i).Label() == "<<ConstExp>>"; i++) {
        symbolKind = "ARRAY";
        op = ARRAY;
        SyntaxNode constExpNode = constDefNode.child(i);
        int constNum = constExpNode.constNumber();
        symbolLength.push_back(constNum);
        size = size * constNum;
    }
    SyntaxNode constInitValNode = constDefNode.child(constDefNode.size() - 1);
    std::string midCodeZ = "";
    if (symbolKind == "ARRAY") {
        midCodeZ = std::to_string(size);
    }
    if (constInitValNode.Label() == "<ConstInitVal>") {
        midCodeZ = initValMidCode(constInitValNode);
    }
    curSymbolTable.addItem(symbolName, symbolAddr, symbolKind,symbolType,
                           symbolConstInt, symbolConstChar, symbolLength);
    midCodeList.push_back(MidCode(op, symbolType, symbolName, midCodeZ));
    return true;
}

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
 * <Exp> → <AddExp>
 */
std::string Parser::expMidCode(SyntaxNode expNode) {
    SyntaxNode addExpNode = expNode.child(0);
    if (addExpNode.Label() == "<AddExp>") {
        return addExpMidCode(addExpNode);
    }
    return "";
}

/*
 * <AddExp> → <MulExp> | <AddExp> (<AddOp>) <MulExp>
 */
std::string Parser::addExpMidCode(SyntaxNode addExpNode) {
    SyntaxNode mulExpNode = addExpNode.child(0);
    std::string mulTemp1 = mulExpMidCode(mulExpNode);
    for (int i = 1; i < addExpNode.size(); i += 2) {
        SyntaxNode addOpNode = addExpNode.child(i);
        SyntaxNode mulExpNode = addExpNode.child(i + 1);
        std::string midCodeZ = allocTempVar();
        std::string mulTemp2 = mulExpMidCode(mulExpNode);
        operation midCodeOp = addOpMidCode(addOpNode);
        midCodeList.push_back(MidCode(midCodeOp, midCodeZ, mulTemp1, mulTemp2));
        freeTempVar();
        mulTemp1 = midCodeZ;
    }
    return mulTemp1;
}

/*
 * <MulExp> → <UnaryExp> | <MulExp> (<MulOp>) <UnaryExp>
 */
std::string Parser::mulExpMidCode(SyntaxNode mulExpNode) {
    SyntaxNode unaryExpNode = mulExpNode.child(0);
    std::string unaryTemp1 = unaryExpMidCode(unaryExpNode);
    for (int i = 1; i < mulExpNode.size(); i += 2) {
        SyntaxNode mulOpNode = mulExpNode.child(i);
        SyntaxNode unaryExpNode = mulExpNode.child(i + 1);
        std::string midCodeZ = allocTempVar();
        std::string unaryTemp2 = mulExpMidCode(mulExpNode);
        operation midCodeOp = mulOpMidCode(mulOpNode);
        midCodeList.push_back(MidCode(midCodeOp, midCodeZ, unaryTemp1, unaryTemp2));
        freeTempVar();
        unaryTemp1 = midCodeZ;
    }
    return unaryTemp1;
}

/*
 * <UnaryExp> → <PrimaryExp> | <Ident> '(' [<FuncRParams>] ')' | <UnaryOp> <UnaryExp>
 */
std::string Parser::unaryExpMidCode(SyntaxNode unaryExpNode) {
    SyntaxNode node = unaryExpNode.child(0);
    if (node.Label() == "<PrimaryExp>") {
        return primaryExpMidCode(node);
    }
    else if (node.Label() == "<UnaryOp>") {
        operation midCodeOp = unaryOpMidCode(node);
        SyntaxNode unaryExpNodeC = unaryExpNode.child(1);
        std::string midCodeY = unaryExpMidCode(unaryExpNodeC);
        std::string midCodeZ = allocTempVar();
        midCodeList.push_back(MidCode(midCodeOp, midCodeZ, "0", midCodeY));
        freeTempVar();
        return midCodeZ;
    }
    return "";
}

/*
 * <PrimaryExp> → '(' <Exp> ')' | <LVal> | <Number>
 */
std::string Parser::primaryExpMidCode(SyntaxNode primaryExpNode) {
    SyntaxNode node = primaryExpNode.child(0);
    if (node.Label() == "<Exp>") {
        return expMidCode(node);
    }
    else if (node.Label() == "<LVal>") {
        return lValMidCode(node);
    }
    else if (node.Label() == "Number") {
        return numberMidCode(node);
    }
    return "";
}

/*
 * <LVal> → <Ident> {'[' <Exp> ']'}
 */
std::string Parser::lValMidCode(SyntaxNode lValNode) {
    SyntaxNode node = lValNode.child(0);
    std::string midCodeX = identMidCode(node);
    Symbol symbol = curSymbolTable.item(midCodeX);
    if (symbol.Kind() == "ARRAY") {
        std::vector<int> length = symbol.Length();
        SyntaxNode expNode = lValNode.child(length.size());
        std::string addX = expMidCode(expNode);
        for (int i = 1; i < length.size(); i++) {
            SyntaxNode expNode = lValNode.child(i);
            std::string mulX = expMidCode(expNode);
            std::string mulY = std::to_string(length[i - 1]);
            std::string mulZ = allocTempVar();
            midCodeList.push_back(MidCode(MULTOP, mulZ, mulX, mulY));
            std::string addZ = allocTempVar();
            midCodeList.push_back(MidCode(PLUSOP, addZ, addX, mulZ));
            addX = addZ;
        }
        for (int i = 1; i < length.size(); i++) {
            freeTempVar();
            freeTempVar();
        }
        return addX;
    } else {
        return symbol.Name();
    }
    return "";
}

/*
 * <AddOp> → '+' | '−'
 */
operation Parser::addOpMidCode(SyntaxNode addOpNode) {
    std::string con = addOpNode.Con();
    if (con == "+") {
        return PLUSOP;
    }
    else if (con == "-") {
        return MINUOP;
    }
    return DEFAULT;
}

/*
 * <MulOp> → '*' | '/' | '%'
 */
operation Parser::mulOpMidCode(SyntaxNode mulOpNode) {
    std::string con = mulOpNode.Con();
    if (con == "*") {
        return MULTOP;
    }
    else if (con == "/") {
        return DIVOP;
    }
    else if (con == "%") {
        return MOBOP;
    }
    return DEFAULT;
}

/*
 * <UnaryOp> → '+' | '−' | '!'
 */
operation Parser::unaryOpMidCode(SyntaxNode unaryOpNode) {
    std::string con = unaryOpNode.Con();
    if (con == "+") {
        return PLUSOP;
    }
    else if (con == "-") {
        return MINUOP;
    } else if (con == "!") {
        return NOTOP;
    }
    return DEFAULT;
}

/*
 * lex IDENFR
 */
std::string Parser::identMidCode(SyntaxNode identNode) {
    return identNode.Con();
}

/*
 * <Number> → <IntConst> | <CharConst>
 */
std::string Parser::numberMidCode(SyntaxNode numberNode) {
    return numberNode.child(0).Con();
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
    }
    return true;
}


