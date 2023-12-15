//
// Created by 77902 on 2023/12/15.
//

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




