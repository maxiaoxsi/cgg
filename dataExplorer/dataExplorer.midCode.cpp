//
// Created by maxiaoxsi on 2023/12/21.
//

#include "dataExplorer.h"

MidCode::MidCode(operation op, std::string z, std::string x, std::string y) {
    _op = op;
    _z = z;
    _x = x;
    _y = y;
}

void MidCode::println() {
    printOp();
    std::cout << " z:" << _z << " x:" <<_x << " y:" << _y << std::endl;
}

void MidCode::printOp() {
    switch(_op) {
        case PLUSOP: // +
            printOp("PLUS");
            break;
        case MINUOP: // -
            printOp("MINU");
            break;
        case MULTOP:// *
            printOp("MULT");
            break;
        case DIVOP: // /
            printOp("DIV");
            break;
        case MOBOP: //%
            printOp("MOB");
            break;
        case LSSOP:  //<
            printOp("LSS");
            break;
        case LEQOP: //<=
            printOp("LEQ");
            break;
        case GREOP: //>
            printOp("GRE");
            break;
        case GEQOP: //>=
            printOp("GEQ");
            break;
        case EQLOP: //==
            printOp("EQL");
            break;
        case NOTOP: //!
            printOp("NOT");
            break;
        case NEQOP: //!=
            printOp("NEQ");
            break;
        case ASSIGNOP: //=
            printOp("ASSIGN");
            break;
        case GOTO:
            printOp("GOTO");
            break;
        case BZ:    //不满足条件跳转
            printOp("BZ");
            break;
        case BNZ:   //满足条件跳转
            printOp("BNZ");
            break;
        case PUSH:
            printOp("PUSH");
            break;
        case RETVALUE: //有返回值函数返回的结果
            printOp("RETVALUE");
            break;
        case SCAN: // scanf
            printOp("SCAN");
            break;
        case PRINT: // printf
            printOp("PRINT");
            break;
        case LABEL:
            printOp("LABEL");
            break;
        case CONST:
            printOp("CONST");
            break;
        case ARRAY: //数组
            printOp("ARRAY");
            break;
        case VAR:
            printOp("VAR");
            break;
        case FUNC: //函数定义
            printOp("FUNC");
            break;
        case PARAM: //函数参数
            printOp("PARAM");
            break;
        case GETARRAY: //取数组的值  t = a[]
            printOp("GETARRAY");
            break;
        case PUTARRAY: //给数组赋值  a[] = t
            printOp("PUTARRAY");
            break;
        case EXIT: //退出 main最后
            printOp("EXIT");
            break;
    }
}

void MidCode::printOp(std::string strOp) {
    std::cout << "op:" << strOp;
}


