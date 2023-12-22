//
// Created by maxiaoxsi on 2023/12/15.
//

#include "parser.h"
/*
 * <Stmt> → <AssignStmt> | [<Exp>] ';' | <Block> | <IfStmt> | <WhileStmt> | <BreakStmt> | <ContinueStmt>
 * | <ReturnStmt> | <PrintfStmt> | <ScanfStmt>
 */
SyntaxNode Parser::isStmt() {
    int idx_ori = _idx;
    SyntaxNode node("<Stmt>");
    // <IfStmt>
    if (isIfTk()) {
        setIdx(_idx - 1);
        SyntaxNode ifStmtNode = isIfStmt();
        if (ifStmtNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(ifStmtNode);
        return node;
    }
    // <WhileStmt>
    if (isWhileTk()) {
        setIdx(_idx - 1);
        SyntaxNode whileStmtNode = isWhileStmt();
        if (whileStmtNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(whileStmtNode);
        return node;
    }
    // <BreakStmt>
    if (isBreakTk()) {
        setIdx(_idx - 1);
        SyntaxNode breakStmtNode = isBreakStmt();
        if (breakStmtNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(breakStmtNode);
        return node;
    }
    // <ContinueStmt>
    if (isContinueTk()) {
        setIdx(_idx - 1);
        SyntaxNode continueStmtNode = isContinueStmt();
        if (continueStmtNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(continueStmtNode);
        return node;
    }
    // <ReturnStmt>
    if (isReturnTk()) {
        setIdx(_idx - 1);
        SyntaxNode returnStmtNode = isReturnStmt();
        if (returnStmtNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(returnStmtNode);
        return node;
    }
    // <PrintStmt>
    if (isPrintfTk()) {
        setIdx(_idx - 1);
        SyntaxNode printfStmtNode = isPrintfStmt();
        if (printfStmtNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(printfStmtNode);
        return node;
    }
    // <ScanfStmt>
    if (isScanfTk()) {
        setIdx(_idx - 1);
        SyntaxNode scanfStmtNode = isScanfStmt();
        if (scanfStmtNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(scanfStmtNode);
        return node;
    }
    // <Block>
    if (isLBrace()) {
        setIdx(_idx - 1);
        SyntaxNode blockNode = isBlock();
        if (blockNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(blockNode);
        return node;
    }
    // empty
    if (isSemicn()) {
        return node;
    }
    //<AssignStmt>
    SyntaxNode assignStmtNode = isAssignStmt();
    if (!assignStmtNode.isNull()) {
        node.addChild(assignStmtNode);
        return node;
    }
    // <Exp>
    SyntaxNode expNode = isExp();
    if (!expNode.isNull()) {
        node.addChild(expNode);
        return node;
    }
    setIdx(idx_ori);
    return {};
}

/*
 * <IfStmt> → 'if' '(' <Cond> ')' <Stmt> [ 'else' <Stmt> ]
 */
SyntaxNode Parser::isIfStmt() {
    int idx_ori = _idx;
    SyntaxNode node("<IfStmt>");
    // 'if'
    if (!isIfTk()) {
        return {};
    }
    // '('
    if (!isLParent()) {
        setIdx(idx_ori);
        return {};
    }
    // <Cond>
    SyntaxNode condNode = isCond();
    if (condNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(condNode);
    // ')'
    if (!isRParent()) {
        setIdx(idx_ori);
        return {};
    }
    // <Stmt>
    SyntaxNode stmtNode = isStmt();
    if (stmtNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(stmtNode);
    // is token 'else'
    if (isElseTk()) {
        stmtNode = isStmt();
        if (stmtNode.isNull()) {
            setIdx(idx_ori);
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
    int idx_ori = _idx;
    SyntaxNode node("<WhileStmt>");
    // 'while'
    if (!isWhileTk()) {
        setIdx(idx_ori);
        return {};
    }
    // '('
    if (!isLParent()) {
        setIdx(idx_ori);
        return {};
    }
    // <Cond>
    SyntaxNode condNode = isCond();
    if (condNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(condNode);
    // ')'
    if (!isRParent()) {
        setIdx(idx_ori);
        return {};
    }
    // <Stmt>
    SyntaxNode stmtNode = isStmt();
    if (stmtNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(stmtNode);
    return node;
}

/*
 * <BreakStmt> → 'break' ';'
 */
SyntaxNode Parser::isBreakStmt() {
    int idx_ori = _idx;
    SyntaxNode node("<BreakStmt>");
    // 'break'
    if (!isBreakTk()) {
        setIdx(idx_ori);
        return {};
    }
    // ';'
    if (!isSemicn()) {
        setIdx(idx_ori);
        return {};
    }
    return node;
}

/*
 * <ContinueStmt> → 'continue' ';'
 */
SyntaxNode Parser::isContinueStmt() {
    int idx_ori = _idx;
    SyntaxNode node("<ContinueStmt>");
    // 'continue'
    if (!isContinueTk()) {
        setIdx(idx_ori);
        return {};
    }
    // ';'
    if (!isSemicn()) {
        setIdx(idx_ori);
        return {};
    }
    return node;
}

/*
 * <ReturnStmt> → 'return' [Exp] ';'
 */
SyntaxNode Parser::isReturnStmt() {
    int idx_ori = _idx;
    SyntaxNode node("<ReturnStmt>");
    if (!isReturnTk()) {
        setIdx(idx_ori);
        return {};
    }
    if (isSemicn()) {
        return node;
    }
    // <Exp>
    SyntaxNode expNode = isExp();
    if (expNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    // ';'
    if (!isSemicn()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(expNode);
    return node;
}

/*
 * <AssignStmt> → <LVal> '=' <Exp> ';'
 */
SyntaxNode Parser::isAssignStmt() {
    int idx_ori = _idx;
    SyntaxNode node("<AssignStmt>");
    // <LVal>
    SyntaxNode lValNode = isLVal();
    if (lValNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(lValNode);
    // '='
    if (!isAssign()) {
        setIdx(idx_ori);
        return {};
    }
    // <Exp>
    SyntaxNode expNode = isExp();
    if (expNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(expNode);
    // ';'
    if (!isSemicn()) {
        setIdx(idx_ori);
        return {};
    }
    return node;
}

/*
 * <PrintfStmt> → 'printf''('<FormatString>{','Exp}')'';'
 */
SyntaxNode Parser::isPrintfStmt() {
    int idx_ori = _idx;
    SyntaxNode node("<PrintfStmt>");
    // 'printf'
    if (!isPrintfTk()) {
        setIdx(idx_ori);
        return {};
    }
    // '('
    if (!isLParent()) {
        setIdx(idx_ori);
        return {};
    }
    // <FormatString>
    SyntaxNode formatStringNode = isFormatString();
    if (formatStringNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(formatStringNode);
    // {','Exp}
    while (isComma()) {
        // <Exp>
        SyntaxNode expNode = isExp();
        if (expNode.isNull()) {
            setIdx(idx_ori);
            return {};
        }
        node.addChild(expNode);
    }
    // ')'
    if (!isRParent()) {
        setIdx(idx_ori);
        return {};
    }
    // ';'
    if (!isSemicn()) {
        setIdx(idx_ori);
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
    int idx_ori = _idx;
    SyntaxNode node("<ThreadFuncDef>");
    // 'Thread'
    if (!isThreadTk()) {
        setIdx(idx_ori);
        return {};
    }
    // '('
    if (!isLParent()) {
        setIdx(idx_ori);
        return {};
    }
    // <FuncDef>
    SyntaxNode funcDefNode = isFuncDef();
    if (funcDefNode.isNull()) {
        setIdx(idx_ori);
        return {};
    }
    node.addChild(funcDefNode);
    // ')'
    if (!isRParent()) {
        setIdx(idx_ori);
        return {};
    }
    return node;
}