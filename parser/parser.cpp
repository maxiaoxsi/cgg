//
// Created by maxiaoxsi on 2023/11/21.
//

#include "parser.h"
#include "../dataExplorer/dataExplorer.h"

Parser::Parser() {
    setIdx(0);
    _tempPool = TempVarPool();
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
    setIdx(_idx - 1);
    while(true) {
        setIdx(_idx + 1);
        if (_token.isConstTk()) {
            setIdx(_idx - 1);
            // <ConstDecl>
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
            // <VarDecl>
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
            if (!setIdx(_idx + 1)) {
                return false;
            }
            if (_token.isMainTk()) {
                setIdx(_idx - 2);
                break;
            }
            else {
                setIdx(_idx - 2);
                // <FuncDef>
                SyntaxNode funcDefNode = isFuncDef();
                if (funcDefNode.isNull()) {
                    return false;
                }
                root.addChild(funcDefNode);
                continue;
            }
        }
        setIdx(_idx - 1);
        break;
    }
    SyntaxNode mainFuncDefNode = isMainFuncDef();
    if (mainFuncDefNode.isNull()) {
        return false;
    }
    root.addChild(mainFuncDefNode);
    return true;
}


/*
 * <BType> → 'int' | 'char'
 */
SyntaxNode Parser::isBType() {
    int idx_ori = _idx;
    SyntaxNode node("<BType>");
    // <BType>
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isBType()) {
        setIdx(idx_ori);
        return {};
    }
    std::string typeStr = _token.typeStr();
    node.setCon(typeStr.substr(0, typeStr.size() - 2));
    return node;
}

/*
 * lex IDENFR
 */
SyntaxNode Parser::isIdent() {
    SyntaxNode node("<Ident>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isIdenfr()) {
        _idx = _idx - 1;
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
        // <Exp>
        SyntaxNode expNode = isExp();
        if (expNode.isNull()) {
            return {};
        }
        node.addChild(expNode);
        // is token comma
        if (!setIdx(_idx + 1)) {
            return {};
        }
    } while(_token.isComma());
    setIdx(_idx - 1);
    return node;
}

/*
 * <Block> → '{' { <BlockItem> } '}'
 */
SyntaxNode Parser::isBlock() {
    int idx_ori = _idx;
    SymbolTable blockTable(curSymbolTable);
    curSymbolTable = blockTable;
    SyntaxNode node("<Block>");
    // '{'
    if (!isLBrace()) {
        setIdx(idx_ori);
        return {};
    }
    // { <BlockItem> } '}'
    while (!isRBrace()) {
        SyntaxNode blockItemNode = isBlockItem();
        if (blockItemNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(blockItemNode);
    }
    curSymbolTable = curSymbolTable.parentTable();
    return node;
}

/*
 * <BlockItem> → <ConstDecl> | <VarDecl> | <Stmt>
 */
SyntaxNode Parser::isBlockItem() {
    int idx_ori = _idx;
    SyntaxNode node("<BlockItem>");
    // is token CONSTTK or <BType> or other
    if (!setIdx(_idx + 1)) {
        setIdx(idx_ori);
        return {};
    }
    if (_token.isConstTk()) {
        setIdx(_idx - 1);
        SyntaxNode constDeclNode = isConstDecl(false);
        if (constDeclNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(constDeclNode);
    }
    else if (_token.isBType()) {
        setIdx(_idx - 1);
        SyntaxNode varDeclNode = isVarDecl(false);
        if (varDeclNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(varDeclNode);
    }
    else {
        setIdx(_idx - 1);
        SyntaxNode stmtNode = isStmt();
        if (stmtNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(stmtNode);
    }
    return node;
}

/*
 * <Cond> → <LOrExp>
 */
SyntaxNode Parser::isCond() {
    SyntaxNode node("<Cond>");
    // <LOrExp>
    SyntaxNode lOrExpNode = isLOrExp();
    if (lOrExpNode.isNull()) {
        return {};
    }
    node.addChild(lOrExpNode);
    return node;
}


/*
 * <FormatString> -> '"' {<char>} '"'
 */
SyntaxNode Parser::isFormatString() {
    SyntaxNode node("<FormatString>");
    if (!isStrCon()) {
        return {};
    }
    node.setCon(_token.tokenCon());
    return node;
}
