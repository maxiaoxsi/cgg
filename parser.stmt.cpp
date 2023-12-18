//
// Created by 77902 on 2023/12/15.
//

#include "parser.h"
/*
 * <Stmt> → <AssignStmt> | [Exp] ';' | <Block> | <IfStmt> | <WhileStmt> | <BreakStmt> | <ContinueStmt>
 * | <ReturnStmt> | <PrintfStmt> | <ScanfStmt>
 */
SyntaxNode Parser::isStmt() {
    SyntaxNode node("<Stmt>");
    // is token while if break ...
    if (!setIdx(_idx + 1)) {
        return {};
    }
    // <IfStmt>
    if (_token.isIfTk()) {
        setIdx(_idx - 1);
        SyntaxNode ifStmtNode = isIfStmt();
        if (ifStmtNode.isNull()) {
            return {};
        }
        node.addChild(ifStmtNode);
    }
    // <WhileStmt>
    else if (_token.isWhileTk()) {
        setIdx(_idx - 1);
        SyntaxNode whileStmtNode = isWhileStmt();
        if (whileStmtNode.isNull()) {
            return {};
        }
        node.addChild(whileStmtNode);
    }
    // <BreakStmt>
    else if (_token.isBreakTk()) {
        setIdx(_idx - 1);
        SyntaxNode breakStmtNode = isBreakStmt();
        if (breakStmtNode.isNull()) {
            return {};
        }
        node.addChild(breakStmtNode);
    }
    // <ContinueStmt>
    else if (_token.isContinueTk()) {
        setIdx(_idx - 1);
        SyntaxNode continueStmtNode = isContinueStmt();
        if (continueStmtNode.isNull()) {
            return {};
        }
        node.addChild(continueStmtNode);
    }
    // <ReturnStmt>
    else if (_token.isReturnTk()) {
        setIdx(_idx - 1);
        SyntaxNode returnStmtNode = isReturnStmt();
        if (returnStmtNode.isNull()) {
            return {};
        }
        node.addChild(returnStmtNode);
    }
    // <PrintStmt>
    else if (_token.isPrintfTk()) {
        setIdx(_idx - 1);
        SyntaxNode printfStmtNode = isPrintfStmt();
        if (printfStmtNode.isNull()) {
            return {};
        }
        node.addChild(printfStmtNode);
    }
    // <ScanfStmt>
    else if (_token.isScanfTk()) {
        setIdx(_idx - 1);
        SyntaxNode scanfStmtNode = isScanfStmt();
        if (scanfStmtNode.isNull()) {
            return {};
        }
        node.addChild(scanfStmtNode);
    }
    //<AssignStmt>
    else if (_token.isIdenfr()) {
        setIdx(_idx - 1);
        SyntaxNode assignStmtNode = isAssignStmt();
        if (assignStmtNode.isNull()) {
            return {};
        }
        node.addChild(assignStmtNode);
    }
    // <Block>
    else if (_token.isLBrace()) {
        setIdx(_idx - 1);
        SyntaxNode blockNode = isBlock();
        if (blockNode.isNull()) {
            return {};
        }
        node.addChild(blockNode);
    }
    // empty
    else if (_token.isSemicn()) {
        return node;
    }
    // <Exp>
    else {
        setIdx(_idx - 1);
        SyntaxNode expNode = isExp();
        if (expNode.isNull()) {
            return {};
        }
        node.addChild(expNode);
        // ';'
        if (!isSemicn()) {
            return {};
        }
    }
    return node;
}

/*
 * <IfStmt> → 'if' '(' <Cond> ')' <Stmt> [ 'else' <Stmt> ]
 */
SyntaxNode Parser::isIfStmt() {
    SyntaxNode node("<IfStmt>");
    // 'if'
    if (!isIfTk()) {
        return {};
    }
    // '('
    if (!isLParent()) {
        return {};
    }
    // <Cond>
    SyntaxNode condNode = isCond();
    if (condNode.isNull()) {
        return {};
    }
    node.addChild(condNode);
    // ')'
    if (!isRParent()) {
        return {};
    }
    // <Stmt>
    SyntaxNode stmtNode = isStmt();
    if (stmtNode.isNull()) {
        return {};
    }
    node.addChild(stmtNode);
    // is token 'else'
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (!_token.isElseTk()) {
        setIdx(_idx - 1);
    }
    else {
        // 'else'
        if (!isElseTk()) {
            return {};
        }
        // <Stmt>
        stmtNode = isStmt();
        if (stmtNode.isNull()) {
            return {};
        }
        node.addChild(stmtNode);
    }
    return node;
}

/*
 * <WhileStmt> → 'while' '(' <Cond> ')' <Stmt>
 */
SyntaxNode Parser::isWhileStmt() {
    SyntaxNode node("<WhileStmt>");
    // 'while'
    if (!isWhileTk()) {
        return {};
    }
    // '('
    if (!isLParent()) {
        return {};
    }
    // <Cond>
    SyntaxNode condNode = isCond();
    if (condNode.isNull()) {
        return {};
    }
    node.addChild(condNode);
    // ')'
    if (!isRParent()) {
        return {};
    }
    // <Stmt>
    SyntaxNode stmtNode = isStmt();
    if (stmtNode.isNull()) {
        return {};
    }
    node.addChild(stmtNode);
    return node;
}

/*
 * <BreakStmt> → 'break' ';'
 */
SyntaxNode Parser::isBreakStmt() {
    SyntaxNode node("<BreakStmt>");
    // 'break'
    if (!isBreakTk()) {
        return {};
    }
    // ';'
    if (!isSemicn()) {
        return {};
    }
    return node;
}
/*
 * <BreakStmt> → 'continue' ';'
 */
SyntaxNode Parser::isContinueStmt() {
    SyntaxNode node("<ContinueStmt>");
    // 'continue'
    if (!isContinueTk()) {
        return {};
    }
    // ';'
    if (!isSemicn()) {
        return {};
    }
    return node;
}

/*
 * <ReturnStmt> → [Exp] ';'
 */
SyntaxNode Parser::isReturnStmt() {
    SyntaxNode node("<ReturnStmt>");
    if (!setIdx(_idx + 1)) {
        return {};
    }
    if (_token.isSemicn()) {
        return node;
    }
    else {
        setIdx(_idx - 1);
        SyntaxNode expNode = isExp();
        if (expNode.isNull()) {
            return {};
        }
        node.addChild(expNode);
        if (!isSemicn()) {
            return {};
        }
    }
    return node;
}

/*
 * <AssignStmt> → <LVal> '=' <Exp> ';'
 */
SyntaxNode Parser::isAssignStmt() {
    SyntaxNode node("<AssignStmt>");
    // <LVal>
    SyntaxNode lValNode = isLVal();
    if (lValNode.isNull()) {
        return {};
    }
    node.addChild(lValNode);
    // '='
    if (!isAssign()) {
        return {};
    }
    // <Exp>
    SyntaxNode expNode = isExp();
    if (expNode.isNull()) {
        return {};
    }
    node.addChild(expNode);
    // ';'
    if (!isSemicn()) {
        return {};
    }
    return node;
}

/*
 * <PrintfStmt> → 'printf''('<FormatString>{','Exp}')'';'
 */
SyntaxNode Parser::isPrintfStmt() {
    SyntaxNode node("<PrintfStmt>");
    // 'printf'
    if (!isPrintfTk()) {
        return {};
    }
    // '('
    if (!isLParent()) {
        return {};
    }
    // <FormatString>
    SyntaxNode formatStringNode = isFormatString();
    if (formatStringNode.isNull()) {
        return {};
    }
    node.addChild(formatStringNode);
    // {','Exp}
    if (!setIdx(_idx + 1)) {
        return {};
    }
    while (_token.isComma()) {
        // <Exp>
        SyntaxNode expNode = isExp();
        if (expNode.isNull()) {
            return {};
        }
        node.addChild(expNode);
    }
    setIdx(_idx - 1);
    // ')'
    if (!isRParent()) {
        return {};
    }
    // ';'
    if (!isSemicn()) {
        return {};
    }
    return node;
}

/*
 * <ScanfStmt> → 'scanf''('<FormatString>{','Exp}')'';'
 */

SyntaxNode Parser::isScanfStmt() {
    SyntaxNode node("<ScanfStmt>");
    // 'scanf'
    if (!isScanfTk()) {
        return {};
    }
    // '('
    if (!isLParent()) {
        return {};
    }
    // <FormatString>
    SyntaxNode formatStringNode = isFormatString();
    if (formatStringNode.isNull()) {
        return {};
    }
    node.addChild(formatStringNode);
    // {','Exp}')'
    if (!setIdx(_idx + 1)) {
        return {};
    }
    while (_token.isComma()) {
        // <Exp>
        SyntaxNode expNode = isExp();
        if (expNode.isNull()) {
            return {};
        }
        node.addChild(expNode);
    }
    setIdx(_idx - 1);
    // ';'
    if (!isSemicn()) {
        return {};
    }
    return node;
}


/*
 * <ThreadFuncDef> → 'Thread' '(' <FuncDef> ')' 
 */
SyntaxNode Parser::isThreadFuncDef(){
    SyntaxNode node("<ThreadFuncDef>");
    // 'Thread'
    if (!isThreadTk()) {
        return {};
    }
    // '('
    if (!isLParent()) {
        return {};
    }
    // <FuncDef>
    SyntaxNode funcDefNode = isFuncDef();
    if (funcDefNode.isNull()) {
        return {};
    }
    node.addChild(funcDefNode);
    // ')'
    if (!isRParent()) {
        return {};
    }
    return node;

}