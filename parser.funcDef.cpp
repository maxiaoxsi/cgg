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
    if (!isFuncTk()) {
        return {};
    }
    // <Ident>
    SyntaxNode identNode = isIdent();
    if (identNode.isNull()) {
        return {};
    }
    node.addChild(identNode);
    // '('
    if (!isLParent()) {
        return {};
    }
    // [FuncFParams]
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isRParent()) {
        setIdx(_idx - 1);
        SyntaxNode funcFParamsNode = isFuncFParams();
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

/*
 * <FuncFParams> → <FuncFParam> { ',' <FuncFParam> }
 */
SyntaxNode Parser::isFuncFParams() {
    SyntaxNode node("<FuncFParams>");
    do {
        // <FuncFParam>
        SyntaxNode FuncFParam = isFuncFParam();
        if (FuncFParam.isNull()) {
            return {};
        }
        node.addChild(FuncFParam);
        // if ','
        if (!setIdx(_idx + 1)) {
            return {};
        }
    } while(_token.isComma());
    setIdx(_idx - 1);
    return node;
}

/*
 * <FuncFParam> → <Ident> <FuncFVarParam> | <Ident> <FuncFArrayParam> | <Ident> <FuncFFuncParam>
 */
SyntaxNode Parser::isFuncFParam() {
    SyntaxNode node("<FuncFParam>");
    // <Ident>
    SyntaxNode identNode = isIdent();
    if (identNode.isNull()) {
        return {};
    }
    node.addChild(identNode);
    // is token '[', 'BType' or 'func'
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (_token.isBType()) {
        setIdx(_idx) - 1;
        // <FuncFVarParam>
        SyntaxNode funcFVarParamNode = isFuncFVarParam();
        if (funcFVarParamNode.isNull()) {
            return {};
        }
        node.addChild(funcFVarParamNode);
    }
    else if (_token.isLParent()) {
        setIdx(_idx - 1);
        // <FuncFArrayParam>
        SyntaxNode funcFArrayParamNode = isFuncFArrayParam();
        if (funcFArrayParamNode.isNull()) {
            return {};
        }
        node.addChild(funcFArrayParamNode);
    }
    else {
        // 'func'
        setIdx(_idx - 1);
        // <FuncFFuncParam>
        SyntaxNode funcFFuncParamNode = isFuncFFuncParam();
        if (funcFFuncParamNode.isNull()) {
            return {};
        }
        node.addChild(funcFFuncParamNode);
    }
    return node;
}

/*
 * <FuncFVarParam> → <BType>
 */

SyntaxNode Parser::isFuncFVarParam() {
    SyntaxNode node("<FuncFParamVar>");
    // <BType>
    SyntaxNode bTypeNode = isBType();
    if (bTypeNode.isNull()) {
        return {};
    }
    node.addChild(bTypeNode);
    return node;
}

/*
 * <FuncFArrayParam> →  '[' ']' { '[' ConstExp ']' } <BType>
 */

SyntaxNode Parser::isFuncFArrayParam() {
    SyntaxNode node("<FuncFArrayParam>");
    // '['
    if (!isLBrack()) {
        return {};
    }
    // ']'
    if (!isRBrack()) {
        return {};
    }
    // is token '['
    if (!setIdx(_idx + 1)) {
        return {};
    }
    while (_token.isLBrack()) {
        // ConstExp
        SyntaxNode  constExpNode = isConstExp();
        if (constExpNode.isNull()) {
            return {};
        }
        node.addChild(constExpNode);
        if (!isRBrack()) {
            return {};
        }
        // is token '['
        if (!setIdx(_idx + 1)) {
            return {};
        }
    }
    setIdx(_idx - 1);
    // <BType>
    SyntaxNode bTypeNode = isBType();
    if (bTypeNode.isNull()) {
        return {};
    }
    node.addChild(bTypeNode);
    return node;
}


/*
 * <FuncFFuncParam> → 'func' '(' {<BType>} ')' <BType>
 */

SyntaxNode Parser::isFuncFFuncParam() {
    SyntaxNode node("<FuncFFuncParam>");
    // 'func'
    if (!isFuncTk()) {
        return {};
    }
    // '('
    if (!isLParent()) {
        return {};
    }
    // is token <BType>
    if (!setIdx(_idx + 1)) {
        return {};
    }
    while (_token.isBType()) {
        setIdx(_idx - 1);
        // <BType>
        SyntaxNode bTypeNode = isBType();
        if (bTypeNode.isNull()) {
            return {};
        }
        node.addChild(bTypeNode);
        if (!setIdx(_idx + 1)) {
            return {};
        }
    }
    setIdx(_idx - 1);
    // ')'
    if (!isRParent()) {
        return {};
    }
    // <BType>
    SyntaxNode bTypeNode = isBType();
    if (bTypeNode.isNull()) {
        return {};
    }
    node.addChild(bTypeNode);
    return node;
}

/*
 * FuncType → [<BType>]
 */
SyntaxNode Parser::isFuncType() {
    SyntaxNode node("<FuncType>");
    // is token <BType>
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (_token.isBType()) {
        setIdx(_idx - 1);
        // <BType>
        SyntaxNode  bTypeNode = isBType();
        if (bTypeNode.isNull()) {
            return {};
        }
        node.addChild(bTypeNode);
    }
    else {
        setIdx(_idx - 1);
    }
    return node;
}

/*
 * <MainFuncDef> → 'int' 'main' '(' ')' <Block>
 */
SyntaxNode Parser::isMainFuncDef() {
    SyntaxNode node("<MainFuncDef>");
    // 'int'
    if (!isIntTk()) {
        return {};
    }
    // 'main'
    if (!isMainTk()) {
        return {};
    }
    // '('
    if (!isLParent()) {
        return {};
    }
    // ')'
    if (!isRParent()) {
        return {};
    }
    // <Block>
    SyntaxNode blockNode = isBlock();
    if (blockNode.isNull()) {
        return {};
    }
    node.addChild(blockNode);
    return node;
}