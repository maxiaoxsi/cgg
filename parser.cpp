//
// Created by mxx on 2023/11/21.
//

#include "parser.h"
#include "dataExplorer.h"

Parser::Parser() {
    setIdx(0);
}
bool Parser::setIdx(int idx) {
    if (idx == -1) {
        _idx = idx;
        return true;
    }
    if (idx >= tokenList.size()) {
        return false;
    }
    _idx = idx;
    _token = tokenList[_idx];
    return true;
}


/*
 * <CompUnit> → {<ConstDecl> | <VarDecl> | <FuncDef>} MainFuncDef
 */
bool Parser::procedure() {
    while(true) {
        if (_token.isConstTk()) {
            setIdx(_idx - 1);
            SyntaxNode constDeclNode = isConstDecl(true);
            if (constDeclNode.isNull()) {
                return false;
            }
            root.addChild(constDeclNode);
            setIdx(_idx + 1);
            continue;
        }
        if (_token.isBType()) {
            setIdx(_idx - 1);
            SyntaxNode varDeclNode = isVarDecl(true);
            if (varDeclNode.isNull()) {
                return false;
            }
            root.addChild(varDeclNode);
            setIdx(_idx + 1);
            continue;
        }
        if (_token.isFuncTk()) {
            // is main?
            setIdx(_idx + 1);
            if (_token.isMainTk()) {
                setIdx(_idx - 2);
                break;
            }
            else {
                setIdx(_idx - 2);
                SyntaxNode funcDefNode = isFuncDef();
                if (funcDefNode.isNull()) {
                    return false;
                }
                root.addChild(funcDefNode);
                setIdx(_idx + 1);
                continue;
            }

            continue;
        }
        break;
    }
    return true;
}


/*
 * <BType> → 'int'
 */
SyntaxNode Parser::isBType() {
    SyntaxNode node("<BType>");
    // <BType>
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isBType()) {
        return {};
    }
    std::string typeStr = _token.typeStr();
    node.setCon(typeStr.substr(0, typeStr.size() - 2));
    return node;
}

/*
 * lex
 */
SyntaxNode Parser::isIdent() {
    SyntaxNode node("<Ident>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isIdenfr()) {
        return {};
    }
    node.setCon(_token.tokenCon());
    return node;
}

/*
 * <FuncRParams> → <Exp> { ',' <Exp> }
 */
SyntaxNode Parser::isFuncRParams() {
    SyntaxNode node("<FuncRParams");
    do {
        SyntaxNode expNode = isExp();
        if (expNode.isNull()) {
            return {};
        }
        node.addChild(expNode);
        if (!setIdx(_idx + 1)) {
            return {};
        }
    } while(_token.isComma());
    setIdx(_idx - 1);
    return node;
}











SyntaxNode Parser::isFuncDecl() {
    return {};
}

SyntaxNode Parser::isMainFuncDecl() {
    return {};
}


