//
// Created by maxiaoxsi on 2023/11/22.
//

#include "dataExplorer.h"
#include <utility>

extern std::vector<LexToken> tokenList = {};

extern SyntaxNode root("<CompUnit>");

extern std::vector<MidCode> midCodeList = {};



LexToken::LexToken() {

}

LexToken::LexToken(typeId typeEnum, const std::string &typeStr, const std::string &tokenCon, int line) {
    _typeEnum = typeEnum;
    _tokenCon = tokenCon;
    _typeStr = typeStr;
    _line = line;
}

/*
void LexToken::println() {
    std::cout << _line << ":" << _typeStr << " " << _tokenCon << std::endl;
}
*/

void SyntaxNode::println(int depth, bool end, std::string &out) {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
        out += "  ";
    }
    if (_con == "") {
        std::cout << _label << std::endl;
        out += _label + "\n";
        return;
    }
    std::cout << _label << ": " << _con << std::endl;
    out += _label + ": " + _con + "\n";
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

bool LexToken::isThreadTk() {
    return _typeEnum == THREAD;
}
bool LexToken::isStrCon() {
    return _typeEnum == STRCON;
}

bool LexToken::isOr() {
    return _typeEnum == OR;
}

bool LexToken::isAnd() {
    return _typeEnum == AND;
}

bool LexToken::isNeq() {
    return _typeEnum == NEQ;
}

bool LexToken::isLss() {
    return _typeEnum == LSS;
}

bool LexToken::isLeq() {
    return _typeEnum == LEQ;
}

bool LexToken::isGre() {
    return _typeEnum == GRE;
}

bool LexToken::isGeq() {
    return _typeEnum == GEQ;
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


void SyntaxNode::println(int depth, bool end, std::string &out) {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
        out += "  ";
    }
    if (_con == "") {
        std::cout << _label << std::endl;
        out += _label + "\n";
        return;
    }
    std::cout << _label << ": " << _con << std::endl;
    out += _label + ": " + _con + "\n";
}

void SyntaxNode::setCon(std::string con) {
    _con = con;
}

/*
void SyntaxNode::printTree() {
    println();
    for (int i = 0; i < _children.size(); i++) {
        _children[i].printTree();
    }
}
*/

void SyntaxNode::printTree(int depth, bool end, std::string &out) {
    println(depth, end, out);
    for (int i = 0; i < _children.size(); i++) {
        _children[i].printTree(depth + 1, end, out);
    }
}

bool SyntaxNode::isNull() {
    return _label == "";
}

std::string SyntaxNode::Con() {
    if (_con != "") {
        return _con;
    }
    for (int i = 0; i < _children.size(); i++) {
        std::string tempCon = _children[i].Con();
        if (_children[i].Con() != "") {
            return tempCon;
        }
    }
    return "";
}

std::string SyntaxNode::Label() {
    return _label;
}

int SyntaxNode::constNumber() {
    return stoi(Con());
}

int SyntaxNode::size() {
    return _children.size();
}

SyntaxNode SyntaxNode::child(int idx) {
    if (idx >= _children.size()) {
        return {};
    }
    return _children[idx];
}

