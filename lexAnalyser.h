//
// Created by maxiaoxsi on 2023/11/10.
//

#ifndef CGG_LEXANALYSER_H
#define CGG_LEXANALYSER_H

#include<iostream>

class LexAnalyser
{
public:
    explicit LexAnalyser(const std::string& file) {
        fileDir = file;
        std::cout << file << std::endl;
    }

private:
    std::string fileDir;
};


#endif