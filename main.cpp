/*
 Sami Badra: masc0673
 
 CS 530, Spring 2015
 Assignment #2, disassembler
 FILE: main.cpp
 
 Copyright (c) 2015 Sami Badra. All rights reserved.
 
 DISCLAIMER: Any unauthorized use, including but not limited to, copying or
 redistributing any chunk of the source code (or an entire file) will result in
 punishment by law. I, Sami Badra, own all rights to the files and their contents.
 */

#include <vector>
#include "OpCode.h"

using namespace std;

#include "Dasm.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>.obj" << endl;
        exit(EXIT_FAILURE);
    }
    Dasm *disassembler = new Dasm;
    disassembler->openFiles(*(argv+1));
    disassembler->disassemble();
    
    return 0;
}
