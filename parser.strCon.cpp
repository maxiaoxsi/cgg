//
// Created by 77902 on 2023/12/15.
//

#include <utility>

#include "parser.h"

bool Parser::isLBrack() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isLBrack()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isRBrack() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isRBrack()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isFuncTk() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isRBrack()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isLParent() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isLParent()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isRParent() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isRParent()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isLBrace() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isLBrace()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isRBrace() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isRBrace()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isSemicn() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isSemicn()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isIfTk() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isIfTk()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isElseTk() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isElseTk()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isWhileTk() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isWhileTk()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isBreakTk() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isBreakTk()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isContinueTk() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isContinueTk()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isPrintfTk() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isPrintfTk()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isScanfTk() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isScanfTk()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isAssign() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isAssign()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isStrCon() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isStrCon()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isIntTk() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isIntTk()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isMainTk() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isMainTk()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isEql() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isEql()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isNeq() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isNeq()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isLss() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isLss()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isLeq() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isLeq()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isGre() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isGre()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isGeq() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isGeq()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isConstTk() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isConstTk()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isComma() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isComma()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isAdd() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isAdd()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}

bool Parser::isMul() {
    if (!setIdx(_idx + 1)) {
        return false;
    }
    if (!_token.isMul()) {
        setIdx(_idx - 1);
        return false;
    }
    return true;
}


