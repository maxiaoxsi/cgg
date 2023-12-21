//
// Created by maxiaoxsi on 2023/12/21.
//

#include "dataExplorer.h"

TempVarPool::TempVarPool() {
    _size = 20;
    _num = 0;
    _idx = 0;
    _tempPool = std::vector<int>(20, 0);
}

std::string TempVarPool::allocTempVar() {
    if (_num == _size) {
        _tempPool.push_back(1);
        for (int i = 0; i < 4; i++) {
            _tempPool.push_back(0);
        }
        _size += 5;
        _num++;
        _idx = _size - 4;
        return genTempVar(_size - 5);
    }
    for (int i = 0; i < _size; i++) {
        int idx = (_idx + i) % _size;
        if (_tempPool[idx] == 0) {
            _tempPool[idx] = 1;
            _idx = idx + 1;
            _num++;
            return genTempVar(idx);
        }
    }
    return "";
}

std::string TempVarPool::genTempVar(int idx) {
    return "~t" + std::to_string(idx);
}

void TempVarPool::freeTempVar(std::string tempVar) {
    int idx = std::stoi(tempVar.substr(2, tempVar.size() - 2));
    _tempPool[idx] = 0;
    _num--;
}