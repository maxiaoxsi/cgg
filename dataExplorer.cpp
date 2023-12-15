//
// Created by 77902 on 2023/11/22.
//

#include "dataExplorer.h"
#include <utility>

extern std::vector<LexToken> tokenList = {};

extern SyntaxNode root("<CompUnit>");

LexToken::LexToken() {

}

LexToken::LexToken(typeId typeEnum, const std::string &typeStr, const std::string &tokenCon, int line) {
    _typeEnum = typeEnum;
    _tokenCon = tokenCon;
    _typeStr = typeStr;
    _line = line;
}

void LexToken::println() {
    std::cout << _line << ":" << _typeStr << " " << _tokenCon << std::endl;
}

typeId LexToken::typeEnum() {
    return _typeEnum;
}

std::string LexToken::typeStr() {
    return _typeStr;
}

std::string LexToken::tokenCon() {
    return _tokenCon;
}

bool LexToken::isLBrack() {
    return _typeEnum == LBRACK;
}

bool LexToken::isRBrack() {
    return _typeEnum == RBRACK;
}

bool LexToken::isLBrace() {
    return _typeEnum == LBRACE;
}

bool LexToken::isRBrace() {
    return _typeEnum == RBRACE;
}

bool LexToken::isEql() {
    return _typeEnum == EQL;
}

bool LexToken::isAssign() {
    return _typeEnum == ASSIGN;
}

bool LexToken::isComma() {
    return _typeEnum == COMMA;
}

bool LexToken::isSemicn() {
    return _typeEnum == SEMICN;
}

bool LexToken::isIntTk() {
    return _typeEnum == INTTK;
}

bool LexToken::isCharTk() {
    return _typeEnum == CHARTK;
}

bool LexToken::isBType() {
    return isIntTk() || isCharTk();
}

bool LexToken::isIdenfr() {
    return _typeEnum == IDENFR;
}

bool LexToken::isConstTk() {
    return _typeEnum == CONSTTK;
}

bool LexToken::isFuncTk() {
    return _typeEnum == FUNCTK;
}

bool LexToken::isPlus() {
    return _typeEnum == PLUS;
}

bool LexToken::isMinu() {
    return _typeEnum == MINU;
}

bool LexToken::isAdd() {
    return isPlus() || isMinu();
}

bool LexToken::isMult() {
    return _typeEnum == MULT;
}

bool LexToken::isDiv() {
    return _typeEnum == DIV;
}

bool LexToken::isMod() {
    return _typeEnum == MOD;
}

bool LexToken::isMul() {
    return isMult() || isDiv() || isMod();
}

bool LexToken::isLParent() {
    return _typeEnum == LPARENT;
}

bool LexToken::isRParent() {
    return _typeEnum == RPARENT;
}

bool LexToken::isUnaryOp() {
    return isPlus() || isMinu() || isNot();
}

bool LexToken::isNot() {
    return _typeEnum == NOT;
}

bool LexToken::isIntCon() {
    return _typeEnum == INTCON;
}

bool LexToken::isCharCon() {
    return _typeEnum == CHARCON;
}

bool LexToken::isNumber() {
    return isIntCon() || isCharCon();
}

bool LexToken::isMainTk() {
    return _typeEnum == MAINTK;
}

bool LexToken::isIfTk() {
    return _typeEnum == IFTK;
}

bool LexToken::isWhileTk() {
    return _typeEnum == WHILETK;
}

bool LexToken::isBreakTk() {
    return _typeEnum == BREAKTK;
}

bool LexToken::isContinueTk() {
    return _typeEnum == CONTINUETK;
}

bool LexToken::isReturnTk() {
    return _typeEnum == RETURNTK;
}

bool LexToken::isPrintfTk() {
    return _typeEnum == PRINTFTK;
}

bool LexToken::isScanfTk() {
    return _typeEnum == SCANFTK;
}

bool LexToken::isElseTk() {
    return _typeEnum == ELSETK;
}

SyntaxNode::SyntaxNode() {
    _label = "";
}

SyntaxNode::SyntaxNode(std::string label) {
    _label = std::move(label);
    _con = "";
    _children = {};
}

void SyntaxNode::addChild(SyntaxNode node) {
    _children.push_back(node);
}

void SyntaxNode::println() {
    std::cout << "label:" << _label << " con:" << _con << std::endl;
}

void SyntaxNode::setCon(std::string con) {
    _con = con;
}

void SyntaxNode::printTree() {
    println();
    for (int i = 0; i < _children.size(); i++) {
        _children[i].printTree();
    }
}

bool SyntaxNode::isNull() {
    return _label == "";
}

