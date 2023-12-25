//
// Created by maxiaoxsi on 2023/12/20.
//

#include "../parser/parser.h"

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
        SyntaxNode mulExpNode2 = addExpNode.child(i + 1);
        operation midCodeOp = addOpMidCode(addOpNode);
        std::string mulTemp2 = mulExpMidCode(mulExpNode2);
        // const
        if (isdigit(mulTemp1[0]) && isdigit(mulTemp2[0])) {
            if (midCodeOp == PLUSOP) {
                mulTemp1 = std::to_string(std::stoi(mulTemp1) + std::stoi(mulTemp2));
            }
            else if (midCodeOp == MINUOP) {
                mulTemp1 = std::to_string(std::stoi(mulTemp1) - std::stoi(mulTemp2));
            }
        }
        // not all const
        else {
            std::string midCodeZ = _tempPool.allocTempVar();
            midCodeList.push_back(MidCode(midCodeOp, midCodeZ, mulTemp1, mulTemp2));
            // freeTempVar
            if (mulTemp1[0] == '~') {
                _tempPool.freeTempVar(mulTemp1);
            }
            if (mulTemp2[0] == '~') {
                _tempPool.freeTempVar(mulTemp2);
            }
            mulTemp1 = midCodeZ;
        }
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
        SyntaxNode unaryExpNode2 = mulExpNode.child(i + 1);
        operation midCodeOp = mulOpMidCode(mulOpNode);
        std::string unaryTemp2 = mulExpMidCode(mulExpNode);
        // all const
        if (isdigit(unaryTemp1[0]) && isdigit(unaryTemp2[0])) {
            if (midCodeOp == MULTOP) {
                unaryTemp1 = std::to_string(std::stoi(unaryTemp1) * std::stoi(unaryTemp2));
            }
            else if (midCodeOp == DIVOP) {
                unaryTemp1 = std::to_string(std::stoi(unaryTemp1) - std::stoi(unaryTemp2));
            }
            else if (midCodeOp == MOBOP) {
                unaryTemp1 = std::to_string(std::stoi(unaryTemp1) % std::stoi(unaryTemp2));
            }
        }
        // not const
        else {
            std::string midCodeZ = _tempPool.allocTempVar();
            midCodeList.push_back(MidCode(midCodeOp, midCodeZ, unaryTemp1, unaryTemp2));
            // freeTempVar
            if (unaryTemp1[0] == '~') {
                _tempPool.freeTempVar(unaryTemp1);
            }
            if (unaryTemp2[0] == '~') {
                _tempPool.freeTempVar(unaryTemp2);
            }
            unaryTemp1 = midCodeZ;
        }
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
        SyntaxNode unaryExpNode2 = unaryExpNode.child(1);
        std::string midCodeY = unaryExpMidCode(unaryExpNode2);
        if (isdigit(midCodeY[0])) {
            if (midCodeOp == PLUSOP) {
                return midCodeY;
            }
            else if (midCodeOp == MINUOP) {
                midCodeY = std::to_string(-std::stoi(midCodeY));
                return midCodeY;
            }
            else if (midCodeOp == NOTOP) {
                midCodeY = std::to_string(!std::stoi(midCodeY));
                return midCodeY;
            }
        }
        std::string midCodeZ = _tempPool.allocTempVar();
        midCodeList.push_back(MidCode(midCodeOp, midCodeZ, "0", midCodeY));
        if (midCodeY[0] == '~') {
            _tempPool.freeTempVar(midCodeY);
        }
        return midCodeZ;
    } else {
        std::string funcDefZ = identMidCode(node);
        if (unaryExpNode.size() > 1) {
            SyntaxNode funcRParamsNode = unaryExpNode.child(1);
            funcRParamsMidCode(funcRParamsNode);
        }
        midCodeList.push_back(MidCode(CALL, "RET", "", ""));
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
    else if (node.Label() == "<Number>") {
        return numberMidCode(node);
    }
    return "";
}

/*
 * <LVal> → <Ident> {'[' <Exp> ']'}
 * identName
 * or
 * GETARRAY tempvar identName idx
 *
 */
std::string Parser::lValMidCode(SyntaxNode lValNode) {
    SyntaxNode identNode = lValNode.child(0);
    std::string getarrayX = identMidCode(identNode);
    Symbol symbol = curSymbolTable.item(getarrayX);
    std::string midCodeX = identMidCode(identNode);
    if (symbol.Kind() == "ARRAY") {
        std::vector<int> length = symbol.Length();
        std::string getarrayY = lValIdxMidCode(lValNode);
        std::string getarrayZ = _tempPool.allocTempVar();
        midCodeList.push_back(MidCode(GETARRAY, getarrayZ, getarrayX, getarrayY));
        if (getarrayX[0] == '~') {
            _tempPool.freeTempVar(getarrayX);
        }
        return getarrayZ;
    }
    // var
    return lValIdentMidCode(lValNode);
}

/*
 * <LVal> → <Ident> {'[' <Exp> ']'}
 */
std::string Parser::lValIdentMidCode(SyntaxNode lValNode) {
    SyntaxNode identNode = lValNode.child(0);
    return identMidCode(identNode);
}

/*
 * <LVal> → <Ident> {'[' <Exp> ']'}
 */
std::string Parser::lValIdxMidCode(SyntaxNode lValNode) {
    SyntaxNode identNode = lValNode.child(0);
    std::string identCon = identMidCode(identNode);
    SyntaxNode expNode = lValNode.child(lValNode.size() - 1);
    Symbol symbol = curSymbolTable.item(identCon);
    std::string addX = expMidCode(expNode);
    for (int i = 1; i < lValNode.size() - 1; i++) {
        SyntaxNode expNode = lValNode.child(i);
        std::string mulX = expMidCode(expNode);
        std::string addY = "0";
        if (isdigit(mulX[0])) {
            addY = std::stoi(mulX) * symbol.arrayMulY(i - 1);
        }
        else {
            std::string mulZ = _tempPool.allocTempVar();
            std::string mulY = std::to_string(symbol.arrayMulY(i - 1));
            midCodeList.push_back(MidCode(MULTOP, mulZ, mulX, mulY));
            if (mulX[0] == '~') {
                _tempPool.freeTempVar(mulX);
            }
            addY = mulZ;
        }
        std::string addZ = "0";
        if (isdigit(addX[0]) && isdigit(addY[0])) {
            addZ = std::to_string(std::stoi(addX) + std::stoi(addY));
        }
        else {
            addZ = _tempPool.allocTempVar();
            midCodeList.push_back(MidCode(PLUSOP, addZ, addX, addY));
            if (addX[0] == '~') {
                _tempPool.freeTempVar(addX);
            }
            if (addY[0] == '~') {
                _tempPool.freeTempVar(addY);
            }
        }
        addX = addZ;
    }
    return addX;
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

