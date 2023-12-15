//
// Created by 77902 on 2023/12/14.
//

#include "parser.h"

/*
 * <Exp> → <AddExp>
 */
SyntaxNode Parser::isExp() {
    SyntaxNode node("<Exp>");
    SyntaxNode addExpNode = isAddExp();
    if (addExpNode.isNull()) {
        return {};
    }
    node.addChild(addExpNode);
    return node;
}

/*
 * <AddExp> → <MulExp> | <AddExp> ('+' | '−') <MulExp>
 */
SyntaxNode Parser::isAddExp() {
    SyntaxNode node("<AddExp>");
    do {
        SyntaxNode mulExpNode = isMulExp();
        if (mulExpNode.isNull()) {
            return {};
        }
        node.addChild(mulExpNode);
        if (!setIdx(_idx + 1)) {
            return {};
        }
    } while(_token.isAdd());
    setIdx(_idx - 1);
    return node;
}

/*
 * <MulExp> → <UnaryExp> | <MulExp> ('*' | '/' | '%') <UnaryExp>
 */
SyntaxNode Parser::isMulExp() {
    SyntaxNode node("<MulExp>");
    do {
        SyntaxNode unaryExpNode = isUnaryExp();
        if (unaryExpNode.isNull()) {
            return {};
        }
        node.addChild(unaryExpNode);
        if (!setIdx(_idx + 1)) {
            return {};
        }
    } while(_token.isMul());
    setIdx(_idx - 1);
    return node;
}

/*
 * <UnaryExp> → <PrimaryExp> | <Ident> '(' [<FuncRParams>]| <UnaryOp> <UnaryExp>
 */
SyntaxNode Parser::isUnaryExp() {
    SyntaxNode node("<UnaryExp>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    //var or func call
    if (_token.isIdenfr()) {
        setIdx(_idx - 1);
        //<Ident>
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
        //')' or <FuncRParams>
        if (!setIdx(_idx + 1)) {
            return {};
        }
        // no paras
        if (_token.isRParent()) {
            //<FuncRParams> without paras
            SyntaxNode funcRParamsNode("<FuncRParams>");
            node.addChild(funcRParamsNode);
        }
            //with paras
        else {
            setIdx(_idx - 1);
            // <FuncRParams>
            SyntaxNode funcRParamsNode = isFuncRParams();
            if (funcRParamsNode.isNull()) {
                return {};
            }
            // ')'
            if (!setIdx(_idx + 1)) {
                return {};
            }
            if (!_token.isRParent()) {
                return {};
            }
        }
        //unary exp with op
    } else if (_token.isUnaryOp()) {
        setIdx(_idx - 1);
        // <UnaryOp>
        SyntaxNode unaryOpNode = isUnaryOp();
        if (unaryOpNode.isNull()) {
            return {};
        }
        node.addChild(unaryOpNode);
        // <UnaryExp>
        SyntaxNode unaryExpNode = isUnaryExp();
        if (unaryOpNode.isNull()) {
            return {};
        }
        node.addChild(unaryExpNode);
    } else {
        setIdx(_idx - 1);
        // <PrimaryExp>
        SyntaxNode primaryExpNode = isPrimaryExp();
        if (primaryExpNode.isNull()) {
            return {};
        }
        node.addChild(primaryExpNode);
    }
    return node;
}

/*
 * <UnaryOp> → '+' | '−' | '!'
 */
SyntaxNode Parser::isUnaryOp() {
    SyntaxNode node("<UnaryOp>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isUnaryOp()) {
        return {};
    }
    node.setCon(_token.tokenCon());
    return node;
}

/*
 * <PrimaryExp> → '(' <Exp> ')' | <LVal> | <Number>
 */
SyntaxNode Parser::isPrimaryExp() {
    SyntaxNode node("<PrimaryExp>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    // '(' <Exp> ')'
    if (_token.isLParent()) {
        // <Exp>
        SyntaxNode expNode = isExp();
        if (expNode.isNull()) {
            return {};
        }
        node.addChild(expNode);
        // ')'
        if (!setIdx(_idx + 1)) {
            return {};
        }
        if (!_token.isRParent()) {
            return {};
        }
    }
        // <Number>
    else if (_token.isNumber()) {
        setIdx(_idx - 1);
        //<Number>
        SyntaxNode numberNode = isNumber();
        if (numberNode.isNull()) {
            return {};
        }
        node.addChild(numberNode);
    }
        // <LVal>
    else {
        setIdx(_idx - 1);
        // <LVal>
        SyntaxNode lValNode = isLVal();
        if (lValNode.isNull()) {
            return {};
        }
        node.addChild(lValNode);
    }
    return node;
}

/*
 * <Number> → <IntConst> | <CharConst>
 */
SyntaxNode Parser::isNumber() {
    SyntaxNode node("<Number>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    //<IntConst>
    if (_token.isIntCon()) {
        setIdx(_idx - 1);
        SyntaxNode intConstNode = isIntConst();
        if (intConstNode.isNull()) {
            return {};
        }
        node.addChild(intConstNode);
    }
    else if (_token.isCharCon()) {
        setIdx(_idx - 1);
        SyntaxNode charConstNode = isCharConst();
        if (charConstNode.isNull()) {
            return {};
        }
        node.addChild(charConstNode);
    }
    else {
        setIdx(_idx - 1);
        return {};
    }
    return node;
}

/*
 * lex INTCON
 */
SyntaxNode Parser::isIntConst() {
    SyntaxNode node("<IntConst>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isIntCon()) {
        return {};
    }
    node.setCon(_token.tokenCon());
    return node;
}

/*
 * lex CHARCON
 */
SyntaxNode Parser::isCharConst() {
    SyntaxNode node("<CharConst>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isCharCon()) {
        return {};
    }
    node.setCon(_token.tokenCon());
    return node;
}

/*
 * <LVal> → <Ident> {'[' <Exp> ']'}
 */
SyntaxNode Parser::isLVal() {
    SyntaxNode node("<LVal>");
    // <Ident>
    SyntaxNode identNode = isIdent();
    if (identNode.isNull()) {
        return {};
    }
    node.addChild(identNode);
    // '['
    if (!setIdx(_idx + 1)) {
        return {};
    }
    // var
    if (!_token.isLBrack()) {
        setIdx(_idx - 1);
        return node;
    }
    // array
    while (_token.isLBrack()) {
        // <Exp>
        SyntaxNode expNode = isExp();
        if (expNode.isNull()) {
            return {};
        }
        // ']'
        if (!setIdx(_idx + 1)) {
            return {};
        }
        if (!_token.isRBrack()) {
            return {};
        }
        // if high level array
        if (!setIdx(_idx + 1)) {
            return {};
        }
    }
    setIdx(_idx - 1);
    return node;
}




