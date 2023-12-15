//
// Created by mxx on 2023/12/14.
//

#include "parser.h"

/*
 * <FuncDef> → 'func' <Ident> '(' [FuncFParams] ')' <FuncType> <Block>
 */
SyntaxNode Parser::isFuncDef() {
    SyntaxNode node("<FuncDef>");
    // 'func'
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isFuncTk()) {
        return {};
    }
    // <Ident>
    SyntaxNode identNode = isIdent();
    if (identNode.isNull()) {
        return {};
    }
    node.addChild(identNode);
    // '('
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isLParent()) {
        return {};
    }
    // [FuncFParams]
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isRParent()) {
        setIdx(_idx - 1);
        SyntaxNode funcFParamsNode = isFuncFParas();
        if (funcFParamsNode.isNull()) {
            return {};
        }
        node.addChild(funcFParamsNode);
        if (!setIdx(_idx + 1)) {
            return {};
        }
    }
    // ')'
    if (!_token.isRParent()) {
        return {};
    }
    // <FuncType>
    SyntaxNode funcTypeNode = isFuncType();
    if (funcTypeNode.isNull()) {
        return {};
    }
    node.addChild(funcTypeNode);
    // <Block>
    SyntaxNode blockNode = isBlock();
    if (blockNode.isNull()) {
        return {};
    }
    node.addChild(blockNode);
    return node;
}
