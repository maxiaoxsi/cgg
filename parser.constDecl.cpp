//
// Created by mxx on 2023/12/14.
//

#include "parser.h"

/*
 * <ConstDecl> → ‘const’ <BType> <ConstDef> {‘,’ <ConstDef>};
 */
SyntaxNode Parser::isConstDecl(bool isGlobal) {
    SyntaxNode node("<ConstDecl>");
    // 'const'
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isConstTk()) {
        return {};
    }
    //<BType>
    SyntaxNode bTypeNode = isBType();
    if (bTypeNode.isNull()) {
        return {};
    }
    node.addChild(bTypeNode);
    do {
        SyntaxNode constDefNode = isConstDef();
        if (constDefNode.isNull()) {
            return {};
        }
        node.addChild(constDefNode);
        if (!setIdx(_idx + 1)) {
            return {};
        }
    } while(_token.isComma());
    if (!_token.isSemicn()) {
        return {};
    }
    return node;
}

/*
 * <ConstDef> → <Ident> { '[' <ConstExp> ']' } '=' <ConstInitVal>
 */
SyntaxNode Parser::isConstDef() {
    SyntaxNode node("<ConstDef>");
    SyntaxNode identNode = isIdent();
    if (identNode.isNull()) {
        return {};
    }
    node.addChild(identNode);
    if (!setIdx(_idx + 1)) {
        return {};
    }
    // multi array
    while (_token.isLBrack()) {
        SyntaxNode constExpNode = isConstExp();
        if (constExpNode.isNull()) {
            return {};
        }
        node.addChild(constExpNode);
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
    if (!_token.isAssign()) {
        return {};
    }
    SyntaxNode constDefVarNode = isConstInitVal();
    if (constDefVarNode.isNull()) {
        return {};
    }
    node.addChild(constDefVarNode);
    return node;
}

/*
 * <ConstInitVal> → <ConstExp> | '{' [ <ConstInitVal> { ',' <ConstInitVal> } ] '}'
 */
SyntaxNode Parser::isConstInitVal() {
    SyntaxNode node("<ConstInitVal>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isLBrace()) {
        setIdx(_idx - 1);
        SyntaxNode constExpNode = isConstExp();
        if (constExpNode.isNull()) {
            return {};
        }
        node.addChild(constExpNode);
        return node;
    }
    do {
        SyntaxNode constInitVarNode = isConstInitVal();
        if (constInitVarNode.isNull()) {
            return {};
        }
        node.addChild(constInitVarNode);
        if (!setIdx(_idx + 1)) {
            return {};
        }
    } while(_token.isRBrace());
    if (!_token.isRBrace()) {
        return {};
    }
    return node;
}

SyntaxNode Parser::isConstExp() {
    SyntaxNode node("<ConstExp>");
    SyntaxNode addExpNode = isAddExp();
    if (addExpNode.isNull()) {
        return {};
    }
    node.addChild(addExpNode);
    return node;
}