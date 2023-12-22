//
// Created by maxiaoxsi on 2023/12/19.
//

#include <utility>
#include <map>
#include "dataExplorer.h"

SymbolTable::SymbolTable() {

}

bool SymbolTable::addItem(std::string name, int addr, std::string kind, std::string type, int constInt,
                          char constChar, std::vector<int> length) {
    if (_table.find(name) == _table.end()) {
        _table[name] = Symbol(name, -1, kind, type, constInt, constChar, length);
        return true;
    }
    return false;
}

SymbolTable SymbolTable::parentTable() {
    return _parent[0];
}

Symbol SymbolTable::item(std::string target) {
    if (_table.find(target) == _table.end()) {
        if (_parent.size()) {
            return {};
        }
        return _parent[0].item(target);
    }
    return _table[target];
}

void SymbolTable::setParent(SymbolTable parent) {
    _parent.push_back(parent);
}

Symbol::Symbol(std::string name, int addr, std::string kind, std::string type, int constInt,
               char constChar, std::vector<int> length) {
    _name = name; // <Ident>
    _kind = kind; //"VAR" "CONST" "FUNC" "ARRAY"
    _type = type; //"INT" "CHAR" ""
    _constInt = constInt; //default = -1
    _constChar = constChar; // default = -1
    _length = length; // default = {}
    _addr = addr; // default = -1
}

Symbol::Symbol() {

}

void Symbol::println() {
    std::cout << _name << " " << _type << " " << _kind << std::endl;
    return;
}

std::string Symbol::Kind() {
    return _kind;
}

std::string Symbol::Name() {
    return _name;
}

std::string Symbol::Type() {
    return _type;
}

std::vector<int> Symbol::Length() {
    return _length;
}

int Symbol::arrayMulY(int idx) {
    int ans = 1;
    for (int i = idx + 1; i < _length.size(); i++) {
        ans = ans * _length[i];
    }
    return ans;
}
