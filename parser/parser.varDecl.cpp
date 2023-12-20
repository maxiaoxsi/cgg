//
// Created by mxx on 2023/12/14.
//
#include "parser.h"

/*
 * <VarDecl> → <BType> <VarDef> { ',' <VarDef> } ';'
 */
SyntaxNode Parser::isVarDecl(bool isGlobal) {
    int idx_ori = _idx;
    SyntaxNode node("<VarDecl>");
    // <BType>
    SyntaxNode bTypeNode = isBType();
    if (bTypeNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(bTypeNode);
    // <VarDef> {',' <VarDef>}
    do {
        // <VarDef>
        SyntaxNode varDefNode = isVarDef();
        if (varDefNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(varDefNode);
    } while (isComma());
    // ';'
    if (!isSemicn()) {
        setIdx(idx_ori);
        return {};
    }
    varDeclMidCode(node);
    return node;
}

/*
 * <VarDef> → <Ident> { '[' <ConstExp> ']' } [ '=' <InitVal> ]
 */
SyntaxNode Parser::isVarDef() {
    int idx_ori = _idx;
    SyntaxNode node("<VarDef>");
    // <Ident>
    SyntaxNode identNode = isIdent();
    if (identNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(identNode);
    // { '[' <ConstExp> ']' }
    while(isLBrack()) {
        // <ConstExp>
        SyntaxNode constExpNode = isConstExp();
        if (constExpNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        // ']'
        if (!isRBrack()) {
            return {};
        }
    }
    // '=' <InitVal>
    if (isAssign()) {
        // <InitVal>
        SyntaxNode initValNode = isInitVal();
        if (initValNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(initValNode);
    }
    return node;
}

/*
 * <InitVal> → <Exp> | '{' [ <InitVal> { ',' InitVal } ] '}'
 */
SyntaxNode Parser::isInitVal() {
    int idx_ori = _idx;
    SyntaxNode node("<InitVal>");
    if (isLBrace()) {
        do {
            // <InitVal>
            SyntaxNode initValNode = isInitVal();
            if (initValNode.isNull()) {
                _idx = idx_ori;
                return {};
            }
            node.addChild(initValNode);
        } while (isComma());
        if (!isRBrace()) {
            _idx = idx_ori;
            return {};
        }
    } else {
        // <Exp>
        SyntaxNode expNode = isExp();
        if (expNode.isNull()) {
            _idx = idx_ori;
            return {};
        }
        node.addChild(expNode);
    }
    return node;
}
