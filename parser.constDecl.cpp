//
// Created by mxx on 2023/12/14.
//

#include "parser.h"

/*
 * <ConstDecl> → ‘const’ <BType> <ConstDef> {‘,’ <ConstDef>} ';'
 */
SyntaxNode Parser::isConstDecl(bool isGlobal) {
    SyntaxNode node("<ConstDecl>");
    // 'const'
    if (!isConstTk()) {
        return {};
    }
    // <BType>
    SyntaxNode bTypeNode = isBType();
    if (bTypeNode.isNull()) {
        return {};
    }
    node.addChild(bTypeNode);
    // <ConstDef> {‘,’ <ConstDef>}
    do {
        SyntaxNode constDefNode = isConstDef();
        if (constDefNode.isNull()) {
            return {};
        }
        node.addChild(constDefNode);
    } while(isComma());
    // ';'
    if (!isSemicn()) {
        return {};
    }
    return node;
}

/*
 * <ConstDef> → <Ident> { '[' <ConstExp> ']' } '=' <ConstInitVal>
 */
SyntaxNode Parser::isConstDef() {
    SyntaxNode node("<ConstDef>");
    // <Ident>
    SyntaxNode identNode = isIdent();
    if (identNode.isNull()) {
        return {};
    }
    node.addChild(identNode);
    // { '[' <ConstExp> ']' }
    while (isLBrack()) {
        // <ConstExp>
        SyntaxNode constExpNode = isConstExp();
        if (constExpNode.isNull()) {
            return {};
        }
        node.addChild(constExpNode);
        // ']'
        if (!isRBrack()) {
            return {};
        }
    }
    // '='
    if (!isAssign()) {
        return {};
    }
    // <ConstInitVal>
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
    if (!isLBrace()) {
        // <ConstExp>
        SyntaxNode constExpNode = isConstExp();
        if (constExpNode.isNull()) {
            return {};
        }
        node.addChild(constExpNode);
        return node;
    }
    // is token '}'
    if (isRBrace()) {
        return node;
    }
    do {
        // <ConstInitVal> { ','< ConstInitVal> }
        // <ConstInitVal>
        SyntaxNode constInitVarNode = isConstInitVal();
        if (constInitVarNode.isNull()) {
            return {};
        }
        node.addChild(constInitVarNode);
    } while(isComma());
    if (!isRBrace()) {
        return {};
    }
    return node;
}

/*
 * <ConstExp> → <AddExp>
 */
SyntaxNode Parser::isConstExp() {
    SyntaxNode node("<ConstExp>");
    // <AddExp>
    SyntaxNode addExpNode = isAddExp();
    if (addExpNode.isNull()) {
        return {};
    }
    node.addChild(addExpNode);
    return node;
}