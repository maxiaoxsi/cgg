//
// Created by mxx on 2023/12/14.
//
#include "parser.h"

/*
 * <VarDecl> → <BType> <VarDef> { ',' <VarDef> } ';'
 */
SyntaxNode Parser::isVarDecl(bool isGlobal) {
    SyntaxNode node("<VarDecl>");
    // <BType>
    SyntaxNode bTypeNode = isBType();
    if (bTypeNode.isNull()) {
        return {};
    }
    node.addChild(bTypeNode);
    // <VarDef> {',' <VarDef>}';'
    do {
        SyntaxNode varDefNode = isVarDef();
        if (varDefNode.isNull()) {
            return {};
        }
        node.addChild(varDefNode);
        if (!setIdx(_idx + 1)) {
            return {};
        }
    } while (_token.isComma());
    if (!_token.isSemicn()) {
        return {};
    }
    return node;
}

/*
 * <VarDef> → <Ident> { '[' <ConstExp> ']' } | <Ident> { '[' <ConstExp> ']' } '=' <InitVal>
 */
SyntaxNode Parser::isVarDef() {
    SyntaxNode node("<VarDef>");
    // <Ident>
    SyntaxNode identNode = isIdent();
    if (identNode.isNull()) {
        return {};
    }
    node.addChild(identNode);
    // { '[' <ConstExp> ']' }
    if (!setIdx(_idx + 1)) {
        return {};
    }
    while(_token.isLBrack()) {
        // <ConstExp>
        SyntaxNode constExpNode = isConstExp();
        if (constExpNode.isNull()) {
            return {};
        }
        // ']'
        if (!setIdx(_idx + 1)) {
            return {};
        }
        if (!_token.isRBrack()) {
            return {};
        }
        if (!setIdx(_idx + 1)) {
            return {};
        }
    }
    // '=' <InitVal>
    if (_token.isAssign()) {
        // <InitVal>
        SyntaxNode initValNode = isInitVal();
        if (initValNode.isNull()) {
            return {};
        }
        node.addChild(initValNode);
    } else {
        setIdx(_idx - 1);
    }
    return node;
}

/*
 * <InitVal> → <Exp> | '{' [ <InitVal> { ',' InitVal } ] '}'
 */
SyntaxNode Parser::isInitVal() {
    SyntaxNode node("<InitVal>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (_token.isLBrace()) {
        do {
            // <InitVal>
            SyntaxNode initValNode = isInitVal();
            if (initValNode.isNull()) {
                return {};
            }
            node.addChild(initValNode);
            // is comma
            if (!setIdx(_idx + 1)) {
                return {};
            }
        } while (_token.isComma());
        if (!_token.isRBrace()) {
            return {};
        }
    } else {
        setIdx(_idx - 1);
        // <Exp>
        SyntaxNode expNode = isExp();
        if (expNode.isNull()) {
            return {};
        }
        node.addChild(expNode);
    }
    return node;
}


