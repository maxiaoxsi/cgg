//
// Created by mxx on 2023/12/14.
//

#include "parser.h"

/*
 * <ConstDecl> → ‘const’ <BType> <ConstDef> {‘,’ <ConstDef>} ';'
 */
SyntaxNode Parser::isConstDecl(bool isGlobal) {
    int idx_ori = _idx;
    SyntaxNode node("<ConstDecl>");
    // 'const'
    if (!isConstTk()) {
        setIdx(idx_ori);
        return {};
    }
    // <BType>
    SyntaxNode bTypeNode = isBType();
    if (bTypeNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(bTypeNode);
    // <ConstDef> {‘,’ <ConstDef>}
    do {
        SyntaxNode constDefNode = isConstDef();
        if (constDefNode.isNull()) {
            _idx = idx_ori;
            return {};
        }
        node.addChild(constDefNode);
    } while(isComma());
    // ';'
    if (!isSemicn()) {
        setIdx(idx_ori);
        return {};
    }
    return node;
}

/*
 * <ConstDef> → <Ident> { '[' <ConstExp> ']' } '=' <ConstInitVal>
 */
SyntaxNode Parser::isConstDef() {
    int idx_ori = _idx;
    SyntaxNode node("<ConstDef>");
    // <Ident>
    SyntaxNode identNode = isIdent();
    if (identNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(identNode);
    // { '[' <ConstExp> ']' }
    while (isLBrack()) {
        // <ConstExp>
        SyntaxNode constExpNode = isConstExp();
        if (constExpNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(constExpNode);
        // ']'
        if (!isRBrack()) {
            _idx = idx_ori;
            return {};
        }
    }
    // '='
    if (!isAssign()) {
        setIdx(idx_ori);
        return {};
    }
    // <ConstInitVal>
    SyntaxNode constDefVarNode = isConstInitVal();
    if (constDefVarNode.isNull()) {
        _idx = idx_ori;
        return {};
    }
    node.addChild(constDefVarNode);
    return node;
}

/*
 * <ConstInitVal> → <ConstExp> | '{' [ <ConstInitVal> { ',' <ConstInitVal> } ] '}'
 */
SyntaxNode Parser::isConstInitVal() {
    int idx_ori = _idx;
    SyntaxNode node("<ConstInitVal>");
    if (!isLBrace()) {
        // <ConstExp>
        SyntaxNode constExpNode = isConstExp();
        if (constExpNode.isNull()) {
            setIdx(idx_ori);
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
            setIdx(idx_ori);
            return {};
        }
        node.addChild(constInitVarNode);
    } while(isComma());
    if (!isRBrace()) {
        setIdx(idx_ori);
        return {};
    }
    return node;
}

/*
 * <ConstExp> → <AddExp>
 */
SyntaxNode Parser::isConstExp() {
    setIdx(idx_ori);
    SyntaxNode node("<ConstExp>");
    // <AddExp>
    SyntaxNode addExpNode = isAddExp();
    if (addExpNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(addExpNode);
    return node;
}