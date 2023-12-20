//
// Created by 77902 on 2023/12/14.
//

#include "parser.h"

/*
 * <Exp> → <AddExp>
 */
SyntaxNode Parser::isExp() {
    int idx_ori = _idx;
    SyntaxNode node("<Exp>");
    SyntaxNode addExpNode = isAddExp();
    if (addExpNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(addExpNode);
    return node;
}

/*
 * <AddExp> → <MulExp> | <AddExp> (<AddOp>) <MulExp>
 */
SyntaxNode Parser::isAddExp() {
    int idx_ori = _idx;
    SyntaxNode node("<AddExp>");
    SyntaxNode addOpNode;
    while(true) {
        // <MulExp>
        SyntaxNode mulExpNode = isMulExp();
        if (mulExpNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(mulExpNode);
        // <AddOp>
        addOpNode = isAddOp();
        if (addOpNode.isNull()) {
            break;
        }
        node.addChild(addOpNode);
    }
    return node;
}

/*
 * <MulExp> → <UnaryExp> | <MulExp> (<MulOp>) <UnaryExp>
 */
SyntaxNode Parser::isMulExp() {
    int idx_ori = _idx;
    SyntaxNode node("<MulExp>");
    SyntaxNode mulOpNode;
    while (true) {
        // <UnaryExp>
        SyntaxNode unaryExpNode = isUnaryExp();
        if (unaryExpNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(unaryExpNode);
        // <MulOp>
        mulOpNode = isMulOp();
        if (mulOpNode.isNull()) {
            break;
        }
        node.addChild(mulOpNode);
    }
    return node;
}

/*
 * <UnaryExp> → <PrimaryExp> | <Ident> '(' [<FuncRParams>] ')' | <UnaryOp> <UnaryExp>
 */
SyntaxNode Parser::isUnaryExp() {
    int idx_ori = _idx;
    SyntaxNode node("<UnaryExp>");
    // is unary exp with op
    // <UnaryOp> <UnaryExp>
    SyntaxNode unaryOpNode = isUnaryOp();
    if (!unaryOpNode.isNull()) {
        node.addChild(unaryOpNode);
        // <UnaryExp>
        SyntaxNode unaryExpNode = isUnaryExp();
        if (unaryOpNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(unaryExpNode);
        return node;
    }
    // is func call
    SyntaxNode identNode = isIdent();
    if (!identNode.isNull()) {
        if (!isLParent()) {
            setIdx(idx_ori);
        }
        // '('
        else {
            node.addChild(identNode);
            //')' or <FuncRParams>
            if (!isRParent()) {
                // <FuncRParams>
                SyntaxNode funcRParamsNode = isFuncRParams();
                if (funcRParamsNode.isNull()) {
                    setIdx(idx_ori);
                    return {};
                }
                node.addChild(funcRParamsNode);
                // ')'
                if (!isRParent()) {
                    setIdx(idx_ori);
                    return {};
                }
            }
            return node;
        }
    }
    // else <PrimaryExp>
    SyntaxNode primaryExpNode = isPrimaryExp();
    if (primaryExpNode.isNull()) {
        _idx = idx_ori;
        return {};
    }
    node.addChild(primaryExpNode);
    return node;
}

/*
 * <PrimaryExp> → '(' <Exp> ')' | <LVal> | <Number>
 */
SyntaxNode Parser::isPrimaryExp() {
    int idx_ori = _idx;
    SyntaxNode node("<PrimaryExp>");
    // is '(' <Exp> ')'
    if (isLParent()) {
        // <Exp>
        SyntaxNode expNode = isExp();
        if (expNode.isNull()) {
            _idx = idx_ori;
            return {};
        }
        node.addChild(expNode);
        // ')'
        if (!isRParent()) {
            _idx = idx_ori;
            return {};
        }
        return node;
    }
    // <Number>
    SyntaxNode numberNode = isNumber();
    if (!numberNode.isNull()) {
        //<Number>
        node.addChild(numberNode);
        return node;
    }
    // <LVal>
    SyntaxNode lValNode = isLVal();
    if (lValNode.isNull()) {
        _idx = idx_ori;
        return {};
    }
    node.addChild(lValNode);
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
        setIdx(_idx - 1);
        return {};
    }
    node.setCon(_token.tokenCon());
    return node;
}

/*
 * <AddOp> → '+' | '−'
 */
SyntaxNode Parser::isAddOp() {
    SyntaxNode node("<AddOp>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isAdd()) {
        setIdx(_idx - 1);
        return {};
    }
    node.setCon(_token.tokenCon());
    return node;
}

/*
 * <MulOp> → '*' | '/' | '%'
 */
SyntaxNode Parser::isMulOp() {
    SyntaxNode node("<MulOp>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isMul()) {
        setIdx(_idx - 1);
        return {};
    }
    node.setCon(_token.tokenCon());
    return node;
}

/*
 * <Number> → <IntConst> | <CharConst>
 */
SyntaxNode Parser::isNumber() {
    int idx_ori = _idx;
    SyntaxNode node("<Number>");
    //<IntConst>
    SyntaxNode intConstNode = isIntConst();
    if (!intConstNode.isNull()) {
        node.addChild(intConstNode);
        return node;
    }
    SyntaxNode charConstNode = isCharConst();
    if (!charConstNode.isNull()) {
        node.addChild(charConstNode);
        return node;
    }
    _idx = idx_ori;
    return {};
}

/*
 * <LVal> → <Ident> {'[' <Exp> ']'}
 */
SyntaxNode Parser::isLVal() {
    int idx_ori = _idx;
    SyntaxNode node("<LVal>");
    // <Ident>
    SyntaxNode identNode = isIdent();
    if (identNode.isNull()) {
        _idx = idx_ori;
        return {};
    }
    node.addChild(identNode);
    // '['
    if (!isLBrack()) {
        return node;
    }
    // array
    do {
        // <Exp>
        SyntaxNode expNode = isExp();
        if (expNode.isNull()) {
            _idx = idx_ori;
            return {};
        }
        // ']'
        if (!isRBrack()) {
            _idx = idx_ori;
            return {};
        }
    } while(isLBrack());
    return node;
}

/*
 * <LOrExp> → <LAndExp> | <LOrExp> '||' <LAndExp>
 */
SyntaxNode Parser::isLOrExp() {
    SyntaxNode node("<LOrExp>");
    do {
        // <LAndExp>
        SyntaxNode lAndExpNode = isLAndExp();
        if (lAndExpNode.isNull()) {
            return {};
        }
        node.addChild(lAndExpNode);
        // is token '||'
        if (!setIdx(_idx + 1)) {
            return {};
        }
    } while(_token.isOr());
    setIdx(_idx - 1);
    return node;
}

/*
 * <LAndExp> → <EqExp> | <LAndExp> '&&' <EqExp>
 */
SyntaxNode Parser::isLAndExp() {
    SyntaxNode node("<LAndExp>");
    do {
        SyntaxNode eqExpNode = isEqExp();
        if (eqExpNode.isNull()) {
            return {};
        }
        node.addChild(eqExpNode);
        // is token '&&'
        if (!setIdx(_idx + 1)) {
            return {};
        }
    } while(_token.isAnd());
    setIdx(_idx - 1);
    return node;
}

/*
 * <EqExp> → <RelExp> | <EqExp> ('==' | '!=') <RelExp>
 */
SyntaxNode Parser::isEqExp() {
    SyntaxNode node("<EqExp>");
    do {
        //<EqExp>
        SyntaxNode eqExpNode = isRelExp();
        if (eqExpNode.isNull()) {
            return {};
        }
        node.addChild(eqExpNode);
    } while(isEql() || isNeq());
    return node;
}

/*
 * <RelExp> → <AddExp> | <RelExp> ('<' | '>' | '<=' | '>=') <AddExp>
 */
SyntaxNode Parser::isRelExp() {
    SyntaxNode node("<RelEqp>");
    do {
        // <AndExp>
        SyntaxNode addExpNode = isAddExp();
        if (addExpNode.isNull()) {
            return {};
        }
        node.addChild(addExpNode);
    } while(isLss() || isLeq() || isGre() ||isGeq());
    return node;
}

/*
 * lex INTCON
 */
SyntaxNode Parser::isIntConst() {
    int ori_idx = _idx;
    SyntaxNode node("<IntConst>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isIntCon()) {
        _idx = ori_idx;
        return {};
    }
    node.setCon(_token.tokenCon());
    return node;
}

/*
 * lex CHARCON
 */
SyntaxNode Parser::isCharConst() {
    int ori_idx = _idx;
    SyntaxNode node("<CharConst>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isCharCon()) {
        _idx = ori_idx;
        return {};
    }
    node.setCon(_token.tokenCon());
    return node;
}

