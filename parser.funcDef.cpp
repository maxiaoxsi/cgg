//
// Created by mxx on 2023/12/14.
//

#include "parser.h"

/*
 * <FuncDef> → 'func' <Ident> '(' [FuncFParams] ')' <FuncType> <Block>
 */
SyntaxNode Parser::isFuncDef() {
    int idx_ori = _idx;
    SyntaxNode node("<FuncDef>");
    // 'func'
    if (!isFuncTk()) {
        _idx = idx_ori;
        return {};
    }
    // <Ident>
    SyntaxNode identNode = isIdent();
    if (identNode.isNull()) {
        _idx = idx_ori;
        return {};
    }
    node.addChild(identNode);
    // '('
    if (!isLParent()) {
        _idx = idx_ori;
        return {};
    }
    // [FuncFParams]
    if (!isRParent()) {
        SyntaxNode funcFParamsNode = isFuncFParams();
        if (funcFParamsNode.isNull()) {
            _idx = idx_ori;
            return {};
        }
        node.addChild(funcFParamsNode);
        // ')'
        if (!isRParent()) {
            _idx = idx_ori;
            return {};
        }
    }
    // <FuncType>
    SyntaxNode funcTypeNode = isFuncType();
    if (funcTypeNode.isNull()) {
        _idx = idx_ori;
        return {};
    }
    node.addChild(funcTypeNode);
    // <Block>
    SyntaxNode blockNode = isBlock();
    if (blockNode.isNull()) {
        _idx = idx_ori;
        return {};
    }
    node.addChild(blockNode);
    return node;
}

/*
 * <FuncFParams> → <FuncFParam> { ',' <FuncFParam> }
 */
SyntaxNode Parser::isFuncFParams() {
    int idx_ori = _idx;
    SyntaxNode node("<FuncFParams>");
    // <FuncFParam> { ',' <FuncFParam> }
    do {
        // <FuncFParam>
        SyntaxNode FuncFParam = isFuncFParam();
        if (FuncFParam.isNull()) {
            _idx = idx_ori;
            return {};
        }
        node.addChild(FuncFParam);
    } while(isComma());
    return node;
}

/*
 * <FuncFParam> → <Ident> <FuncFVarParam> | <Ident> <FuncFArrayParam> | <Ident> <FuncFFuncParam>
 */
SyntaxNode Parser::isFuncFParam() {
    int idx_ori = _idx;
    SyntaxNode node("<FuncFParam>");
    // <Ident>
    SyntaxNode identNode = isIdent();
    if (identNode.isNull()) {
        _idx = idx_ori;
        return {};
    }
    node.addChild(identNode);
    // is token '[', 'BType' or 'func'
    if (!setIdx(_idx + 1)) {
        _idx = idx_ori;
        return {};
    }
    if (_token.isBType()) {
        setIdx(_idx - 1);
        // <FuncFVarParam>
        SyntaxNode funcFVarParamNode = isFuncFVarParam();
        if (funcFVarParamNode.isNull()) {
            _idx = idx_ori;
            return {};
        }
        node.addChild(funcFVarParamNode);
    }
    else if (_token.isLBrack()) {
        setIdx(_idx - 1);
        // <FuncFArrayParam>
        SyntaxNode funcFArrayParamNode = isFuncFArrayParam();
        if (funcFArrayParamNode.isNull()) {
            _idx = idx_ori;
            return {};
        }
        node.addChild(funcFArrayParamNode);
    }
    else {
        setIdx(_idx - 1);
        // <FuncFFuncParam>
        SyntaxNode funcFFuncParamNode = isFuncFFuncParam();
        if (funcFFuncParamNode.isNull()) {
            _idx = idx_ori;
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
    int idx_ori = _idx;
    SyntaxNode node("<FuncFParamVar>");
    // <BType>
    SyntaxNode bTypeNode = isBType();
    if (bTypeNode.isNull()) {
        _idx = idx_ori;
        return {};
    }
    node.addChild(bTypeNode);
    return node;
}

/*
 * <FuncFArrayParam> →  '[' ']' { '[' ConstExp ']' } <BType>
 */

SyntaxNode Parser::isFuncFArrayParam() {
    int idx_ori = _idx;
    SyntaxNode node("<FuncFArrayParam>");
    // '['
    if (!isLBrack()) {
        _idx = idx_ori;
        return {};
    }
    // ']'
    if (!isRBrack()) {
        _idx = idx_ori;
        return {};
    }
    // { '[' ConstExp ']' }
    while (isLBrack()) {
        // ConstExp
        SyntaxNode  constExpNode = isConstExp();
        if (constExpNode.isNull()) {
            _idx = idx_ori;
            return {};
        }
        node.addChild(constExpNode);
        if (!isRBrack()) {
            _idx = idx_ori;
            return {};
        }
    }
    // <BType>
    SyntaxNode bTypeNode = isBType();
    if (bTypeNode.isNull()) {
        _idx = idx_ori;
        return {};
    }
    node.addChild(bTypeNode);
    return node;
}


/*
 * <FuncFFuncParam> → '(' {<BType>} ')' <BType>
 */
SyntaxNode Parser::isFuncFFuncParam() {
    int idx_ori = _idx;
    SyntaxNode node("<FuncFFuncParam>");
    // '('
    if (!isLParent()) {
        _idx = idx_ori;
        return {};
    }
    // is token <BType>
    if (!isRParent()) {
        do {
            SyntaxNode bTypeNode = isBType();
            if (bTypeNode.isNull()) {
                _idx = idx_ori;
                return {};
            }
            node.addChild(bTypeNode);
        } while (isComma());
        if (!isRParent()) {
            _idx = idx_ori;
            return {};
        }
    }
    // <BType>
    SyntaxNode bTypeNode = isBType();
    if (bTypeNode.isNull()) {
        _idx = idx_ori;
        return {};
    }
    node.addChild(bTypeNode);
    return node;
}

/*
 * <FuncType> → [<BType>]
 */
SyntaxNode Parser::isFuncType() {
    int idx_ori = _idx;
    SyntaxNode node("<FuncType>");
    // <BType>
    SyntaxNode bTypeNode = isBType();
    if (bTypeNode.isNull()) {
        return node;
    }
    node.addChild(bTypeNode);
    return node;
}

/*
 * <MainFuncDef> → 'func' 'main' '(' ')' <FuncType> <Block>
 */
SyntaxNode Parser::isMainFuncDef() {
    int idx_ori = _idx;
    SyntaxNode node("<MainFuncDef>");
    // 'func'
    if (!isFuncTk()) {
        setIdx(idx_ori);
        return {};
    }
    // 'main'
    if (!isMainTk()) {
        setIdx(idx_ori);
        return {};
    }
    // '('
    if (!isLParent()) {
        setIdx(idx_ori);
        return {};
    }
    // ')'
    if (!isRParent()) {
        setIdx(idx_ori);
        return {};
    }
    // <FuncType>
    SyntaxNode funcTypeNode = isFuncType();
    if (funcTypeNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(funcTypeNode);
    // <Block>
    SyntaxNode blockNode = isBlock();
    if (blockNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(blockNode);
    return node;
}