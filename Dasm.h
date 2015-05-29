/*
 Sami Badra: masc0673
 Genaro Orodio, masc0633
 Daniel Silva, masc0624
 
 CS 530, Spring 2015
 Assignment #2, disassembler
 FILE: Dasm.h
 
 Copyright (c) 2015 Sami Badra. All rights reserved.
 */

#ifndef __a2__C_____Dasm__
#define __a2__C_____Dasm__

#include <stdio.h>
#include "OpCode.h"
class Dasm {
public:
    void openFiles(char *objFile);
    void disassemble();
private:
    int instructionAnalyzer(int row, int current);
    void analyzeFormat1(OpCode code, int opCode, int row, int current);
    void analyzeFormat2(OpCode code, int opCode, int row, int current);
    int analyzeFormat3(OpCode code, int opCode, int row, int current);
    void headerRecordAnalyzer(int row);
    void textRecordAnalyzer(int row);
    void modifyRecordAnalyzer(int row);
    void endRecordAnalyzer(int row);
    void loadDataStorage();
    vector<string> objStorage;
    vector<string> symStorage;
    vector<string> litNames;
    vector<int> litLengths;
    vector<unsigned int> litAddresses;
    vector<string> symNames;
    vector<unsigned int> symValues;
    vector<char> symFlags;
    unsigned int progLength;
    unsigned int currentAddress;
    unsigned int baseAddress;
};
#endif /* defined(__a2__C_____Dasm__) */
