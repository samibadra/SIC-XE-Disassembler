/*
 Sami Badra: masc0673
 
 CS 530, Spring 2015
 Assignment #2, disassembler
 FILE: OpCode.h
 
 Copyright (c) 2015 Sami Badra. All rights reserved.
 
 DISCLAIMER: Any unauthorized use, including but not limited to, copying or
 redistributing any chunk of the source code (or an entire file) will result in
 punishment by law. I, Sami Badra, own all rights to the files and their contents.
 */

#ifndef __a2__C_____OpCode__
#define __a2__C_____OpCode__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

class OpCode {
public:
    bool getBit(int input, int position);
    string getOpName(int opCode);
    int getOpFormat(int opCode);
};
#endif /* defined(__a2__C_____OpCode__) */
