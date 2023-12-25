//
// Created by maxiaoxsi on 2023/11/22.
//

#ifndef CGG_DATAEXPLORER_H
#define CGG_DATAEXPLORER_H

#include <iostream>
#include <vector>
#include <map>

enum typeId {
    CONSTTK, INTTK, CHARTK, VOIDTK, MAINTK, IFTK, ELSETK, DOTK, WHILETK, FORTK, SCANFTK,
    PRINTFTK, RETURNTK, FUNCTK, BREAKTK, CONTINUETK, //tks
    IDENFR, INTCON, CHARCON, STRCON,
    PLUS, MINU, MULT, DIV, MOD,// operators
    LSS, LEQ, GRE, GEQ, EQL, NEQ, // compares
    OR, AND, NOT, // logic ops
    ASSIGN, SEMICN, COMMA,
    LPARENT, RPARENT, LBRACK, RBRACK, LBRACE, RBRACE, //brackets
    THREAD
};

enum operation {
    DEFAULT,// default
    PLUSOP, MINUOP, MULTOP, DIVOP, MOBOP,  // operators
    LSSOP,  //<
    LEQOP,  //<=
    GREOP,  //>
    GEQOP,  //>=
    EQLOP,  //==
    NOTOP, // !
    NEQOP,  //!=
    ASSIGNOP,  //=
    GOTO,  //无条件跳转
    BZ,    //不满足条件跳转
    BNZ,   //满足条件跳转
    PUSH,  //函数调用时参数传递
    CALL,  //函数调用
    RET,   //函数返回语句
    RETVALUE, //有返回值函数返回的结果
    SCAN,  //读
    PRINT, //写
    LABEL, //标号
    CONST, //常量
    ARRAY, //数组
    VAR,   //变量
    FUNC,  //函数定义
    PARAM, //函数参数
    GETARRAY,  //取数组的值  t = a[]
    PUTARRAY,  //给数组赋值  a[] = t
    EXIT,  //退出 main最后
};

class LexToken {
public:
    LexToken(typeId typeEnum, const std::string &typeStr, const std::string &tokenCon, int line);
    LexToken();
    void println();
    std::string typeStr();
    std::string tokenCon();
    bool isLParent();
    bool isRParent();
    bool isLBrack();
    bool isRBrack();
    bool isLBrace();
    bool isRBrace();
    bool isComma();
    bool isSemicn();
    bool isEql();
    bool isNeq();
    bool isAssign();
    bool isIntTk();
    bool isCharTk();
    bool isBType();
    bool isIdenfr();
    bool isConstTk();
    bool isFuncTk();
    bool isPlus();
    bool isMinu();
    bool isAdd();
    bool isMult();
    bool isDiv();
    bool isMod();
    bool isMul();
    bool isUnaryOp();
    bool isIntCon();
    bool isCharCon();
    bool isNumber();
    bool isMainTk();
    bool isIfTk();
    bool isWhileTk();
    bool isBreakTk();
    bool isContinueTk();
    bool isReturnTk();
    bool isPrintfTk();
    bool isScanfTk();
    bool isElseTk();
    bool isThreadTk();
    bool isStrCon();
    bool isNot();
    bool isOr();
    bool isAnd();
    bool isLss();
    bool isLeq();
    bool isGre();
    bool isGeq();
    typeId typeEnum();

private:
    std::string _tokenCon;
    std::string _typeStr;
    typeId _typeEnum;
    int _line;
};

class SyntaxNode {
public:
    explicit SyntaxNode(std::string label);
    SyntaxNode();
    void addChild(SyntaxNode child);
    void printTree(int depth, bool end, std::string &out);
    void setCon(std::string con);
    std::string Con();
    std::string Label();
    int constNumber();
    void println(int depth, bool end, std::string &out);
    bool isNull();
    int size();
    SyntaxNode child(int idx);
private:
    std::string _label;
    std::string _con;
    std::vector<SyntaxNode> _children;
};

class MidCode {         //z = x op y
public:
    MidCode(operation op, std::string z, std::string x, std::string y);
    void println();
    void printOp();
    void printOp(std::string strOp);
private:
    operation _op;      // 操作
    std::string _z;     // 结果
    std::string _x;     // 左操作数
    std::string _y;     // 右操作数
};

class Symbol {
public:
    std::string Name();
    std::string Kind();
    std::string Type();
    std::vector<int> Length();
    Symbol(std::string name, int addr, std::string kind, std::string type, int constInt,
           char constChar, std::vector<int> length);
    Symbol();
    void println();
    int arrayMulY(int idx);
private:
    std::string _name;
    std::string _kind; //"VAR" "CONST" "FUNC" "ARRAY" "ARRAY"
    std::string _type; //"INT" "CHAR" "VOID"
    int _constInt;
    char _constChar;
    std::vector<int> _length;  //数组长度  对于函数用于记录这个函数有多少变量（参数+局部变量+临时)
    std::vector<std::string> _parameterTable;  //参数类型
    int _addr;   //地址
};

class SymbolTable{
public:
    SymbolTable();
    SymbolTable(SymbolTable const &parent);
    bool addItem(std::string name, int addr, std::string kind, std::string type, int constInt,
                 char constChar, std::vector<int> length);
    SymbolTable parentTable();
    Symbol item(std::string target);
private:
    std::map<std::string, Symbol> _table;
    std::vector<SymbolTable>  _parent;
};

class TempVarPool{
public:
    TempVarPool();
    std::string allocTempVar();
    std::string genTempVar(int idx);
    void freeTempVar(std::string tempVar);
private:
    int _num = 0;
    int _idx = 0;
    int _size = 0;
    std::vector<int> _tempPool;
};

extern std::vector<LexToken> tokenList;

extern std::vector<MidCode> midCodeList;

extern SyntaxNode root;

#endif //CGG_DATAEXPLORER_H
