//
// Created by maxiaoxsi on 2023/12/21.
//

#include "../parser/parser.h"

/*
 * <FuncDef> → 'func' <Ident> '(' [FuncFParams] ')' <FuncType> <Block>
 * funcFParamsMidCode
 * func  funcName '' type
 */
bool Parser::funcDefMidCode(SyntaxNode funcDefNode) {
    SyntaxNode identNode = funcDefNode.child(0);
    SyntaxNode funcTypeNode = funcDefNode.child(funcDefNode.size() - 2);
    std::string funcZ = identMidCode(identNode);
    std::string funcX = funcTypeMidCode(funcTypeNode);
    midCodeList.push_back(MidCode(FUNC, funcZ, funcX, ""));
    SyntaxNode funcFParamsNode = funcDefNode.child(1);
    if (funcFParamsNode.Label() == "<FuncFParams>") {
        funcFParamsMidCode(funcFParamsNode);
    }
    return true;
}

/*
 * <FuncFParams> → <FuncFParam> { ',' <FuncFParam> }
 * funcFParamMidCode
 */
bool Parser::funcFParamsMidCode(SyntaxNode funcFParamsNode) {
    for (int i = 0; i < funcFParamsNode.size(); i++) {
        SyntaxNode funcFParamNode = funcFParamsNode.child(i);
        funFParamMidCode(funcFParamNode);
    }
    return false;
}
/*
 * <FuncFParam> → <Ident> <FuncFVarParam> | <Ident> <FuncFArrayParam> | <Ident> <FuncFFuncParam>
 * param identName type ""
 */
bool Parser::funFParamMidCode(SyntaxNode funcFParamNode) {
    SyntaxNode identNode = funcFParamNode.child(0);
    std::string paraZ = identMidCode(identNode);
    SyntaxNode node = funcFParamNode.child(1);
    std::string paraX = "";
    if (node.Label() == "<FuncFVarParam>") {
        paraX = funcFVarParamMidCode(node);
    }
    midCodeList.push_back(MidCode(PARAM, paraZ, paraX, ""));
    return true;
}

/*
 * <FuncType> → [<BType>]
 */
std::string Parser::funcTypeMidCode(SyntaxNode funcTypeNode) {
    if (funcTypeNode.size() == 0) {
        return "";
    }
    SyntaxNode bTypeNode = funcTypeNode.child(0);
    return bTypeMidCode(bTypeNode);
}

/*
 * <FuncRParams> → <Exp> { ',' <Exp> }
 */
bool Parser::funcRParamsMidCode(SyntaxNode funcRParamsNode) {
    for (int i = 0; i < funcRParamsNode.size(); i++) {
        SyntaxNode expNode = funcRParamsNode.child(i);
        std::string pushZ = expMidCode(expNode);
        midCodeList.push_back(MidCode(PUSH, pushZ, "", ""));
        if (pushZ[0] == '~') {
            _tempPool.freeTempVar(pushZ);
        }
    }
    return true;
}

/*
 * <FuncFVarParam> → <BType>
 * bTypeMidCode
 */
std::string Parser::funcFVarParamMidCode(SyntaxNode funcFVarParamNode) {
    SyntaxNode bTypeNode = funcFVarParamNode.child(0);
    return bTypeMidCode(bTypeNode);
}
