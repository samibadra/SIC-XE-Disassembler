/*
 Sami Badra: masc0673
 Genaro Orodio, masc0633
 Daniel Silva, masc0624
 
 CS 530, Spring 2015
 Assignment #2, disassembler
 FILE: Dasm.cpp
 
 Copyright (c) 2015 Sami Badra. All rights reserved.
 */

#include "Dasm.h"
#include <iomanip>

ifstream objStream;
ifstream symStream;
ofstream sicStream;
ofstream lisStream;

// copies contents of files into storage (vectors)
void Dasm::loadDataStorage() {
    string fileLine;
    while (objStream.good()) {
        getline(objStream, fileLine);
        objStorage.push_back(fileLine);
    }
    while (symStream.good()) {
        getline(symStream, fileLine);
        symStorage.push_back(fileLine);
    }
    int i = 2;
    for (i = 2; i < symStorage.size()-1; i++) {
        if (symStorage[i][0] != (char)NULL) {
            symNames.push_back(symStorage[i].substr(0, 6));
            symValues.push_back((unsigned int)strtol(symStorage[i].substr(8, 6).c_str(), NULL, 16));
            symFlags.push_back((unsigned int)strtol(symStorage[i].substr(16, 1).c_str(), NULL, 16));
        }
        else {
            i += 3;
            break;
        }
    }
    for (int j = i; j<symStorage.size()-1; j++) {
        litNames.push_back(symStorage[j].substr(8, 6));
        litLengths.push_back((int)strtol(symStorage[i].substr(19, 1).c_str(), NULL, 16));
        litAddresses.push_back((unsigned int)strtol(symStorage[i].substr(24, 6).c_str(), NULL, 16));
    }
}

// reads an object file and sym file
void Dasm::openFiles(char *objFile) {
    objStream.open(objFile);
    if (!objStream.is_open()) {
        cout << "'.obj' file not found." << endl;
        exit(EXIT_FAILURE);
    }
    
    string symFile = objFile;
    symFile.erase(symFile.find_last_of('.'));
    symFile.append(".sym");
    symStream.open(symFile.c_str());
    if (!symStream.is_open()){
        cout << "'.sym' file not found." << endl;
        exit(EXIT_FAILURE);
    }
    string sicFile = objFile;
    sicFile.erase(symFile.find_last_of("."));
    sicFile.append(".sic");
    sicStream.open (sicFile.c_str());
    
    string lisFile = objFile;
    lisFile.erase(lisFile.find_last_of("."));
    lisFile.append(".lis");
    lisStream.open (lisFile.c_str());
    loadDataStorage();
    
    objStream.close();
    symStream.close();
}

void Dasm::analyzeFormat1(OpCode code, int opCode, int row, int current) {
    string opName = code.getOpName(opCode);
    
    for (int i = 0; i < symValues.size()-1; i++) { //check if symbol name should be inserted
        if (currentAddress == symValues[i]) {
            sicStream << setw(8) << left << symNames[i];
            lisStream << setw(8) << left << symNames[i];
            break;
        }
        else if (i+1 >= symValues.size()-1) {
            sicStream << "         " << setw(7) << left << opName;
            lisStream << "         " << setw(7) << left << opName;
        }
    }
    
    for (int i = 0; i < litNames.size(); i++) { //check if literal should be inserted
        if (currentAddress == litAddresses[i]) {
            sicStream << setw(10) << left << litNames[i] << endl;
            sicStream << setw(14) << right << "LTORG" << endl;
            lisStream << setw(10) << left << litNames[i] << endl;
            lisStream << setw(14) << right << "LTORG" << endl;
            return;
        }
    }
}

void Dasm::analyzeFormat2(OpCode code, int opCode, int row, int current) {
    string opName = code.getOpName(opCode);
    
    for (int i = 0; i < symValues.size()-1; i++) { //check if symbol name should be inserted
        if (currentAddress == symValues[i]) {
            sicStream << setw(8) << left << symNames[i];
            lisStream << setw(8) << left << symNames[i];
            break;
        }
        else if (i+1 >= symValues.size()-1) {
            sicStream << "         " << setw(7) << left << opName;
            lisStream << "         " << setw(7) << left << opName;
        }
    }
    
    for (int i = 0; i < litNames.size(); i++) { //check if literal should be inserted
        if (currentAddress == litAddresses[i]) {
            sicStream << setw(10) << left << litNames[i] << endl;
            sicStream << setw(14) << right << "LTORG" << endl;
            lisStream << setw(10) << left << litNames[i] << endl;
            lisStream << setw(14) << right << "LTORG" << endl;
            return;
        }
    }
    int r1 = (int)strtol(objStorage[row].substr(current+2, 1).c_str(), NULL, 16);
    int r2 = (int)strtol(objStorage[row].substr(current+3, 1).c_str(), NULL, 16);
    
    switch (r1) {           //output register name for first register operand
        case 0:
            sicStream << "A,";
            lisStream << "A,";
            break;
        case 1:
            sicStream << "X,";
            lisStream << "X,";
            break;
        case 2:
            sicStream << "L,";
            lisStream << "L,";
            break;
        case 3:
            sicStream << "B,";
            lisStream << "B,";
            break;
        case 4:
            sicStream << "S,";
            lisStream << "S,";
            break;
        case 5:
            sicStream << "T,";
            lisStream << "T,";
            break;
        case 6:
            sicStream << "F,";
            lisStream << "F,";
            break;
        default:
            break;
    }
    switch (r2) {           //output register name for 2nd operand
        case 0:
            sicStream << "A" << endl;
            lisStream << "A" << endl;
            break;
        case 1:
            sicStream << "X" << endl;
            lisStream << "X" << endl;
            break;
        case 2:
            sicStream << "L" << endl;
            lisStream << "L" << endl;
            break;
        case 3:
            sicStream << "B" << endl;
            lisStream << "B" << endl;
            break;
        case 4:
            sicStream << "S" << endl;
            lisStream << "S" << endl;
            break;
        case 5:
            sicStream << "T" << endl;
            lisStream << "T" << endl;
            break;
        case 6:
            sicStream << "F" << endl;
            lisStream << "F" << endl;
            break;
        default:
            break;
    }
}

int Dasm::analyzeFormat3(OpCode code, int opCode, int row, int current) {
    string opName = code.getOpName(opCode);
    bool nixbpe[6];
    int flagSection = (int)strtol(objStorage[row].substr(current+1, 2).c_str(), NULL, 16);
    for (int i = 0; i < 6; i++)           //set flags bits for nixbpe
        nixbpe[i] = code.getBit(flagSection, 5-i);
    
    unsigned int instruction = (unsigned int)strtol(objStorage[row].substr(current, 2*(3+nixbpe[5])).c_str(), NULL, 16);
    for (int i = 0; i < symValues.size()-1; i++) { //check if symbol name should be inserted
        if (currentAddress == symValues[i]) {
            sicStream << setw(8) << left << symNames[i];
            lisStream << setw(8) << left << symNames[i];
            break;
        }
        else if (i+1 >= symValues.size()-1) {
            sicStream << "        ";
            lisStream << "        ";
        }
    }
    
    for (int i = 0; i < litNames.size(); i++) { //check if literal should be inserted
        if (currentAddress == litAddresses[i]) {
            int literal = (int)strtol(objStorage[row].substr(current+(2*(3+nixbpe[5])), litLengths[i]).c_str(), NULL, 16);
            sicStream << (nixbpe[5] ? "+":" "); //insert a "+" if extended format
            sicStream << setw(7) << opName << setw(10) << left << litNames[i] << endl;
            sicStream << setw(14) << right << "LTORG" << endl;
            lisStream << (nixbpe[5] ? "+":" "); //insert a "+" if extended format
            lisStream << setw(7) << left << opName << setw(10) << left << litNames[i];
            lisStream << setfill('0') << right << setw(2*(3+nixbpe[5])) << instruction << setfill(' ') << endl;
            lisStream << setfill('0') << setw(4) << right << currentAddress << setfill(' ') << "  ";
            lisStream << setw(14) << right << "LTORG" << "            " << literal << endl;
            return (3 + (litLengths[i]/2));
        }
    }
    
    sicStream << (nixbpe[5] ? "+":" "); //insert a "+" if extended format
    lisStream << (nixbpe[5] ? "+":" ");
    
    unsigned int targetAddress = 0;
    if (nixbpe[5]) {                    //check for extended format and put displacement field into targetAddress
        targetAddress = (unsigned int)strtol(objStorage[row].substr(current, 8).c_str(), NULL, 16);
        targetAddress &= 0x000FFFFF;
    }
    else {
        targetAddress = (unsigned int)strtol(objStorage[row].substr(current, 6).c_str(), NULL, 16);
        targetAddress &= 0x000FFF;
    }
    
    if (nixbpe[3]) {        //base relative
        targetAddress += baseAddress;
    }
    else if (nixbpe[4]) {   //PC relative
        targetAddress += (currentAddress + 3);
    }
    
    if (opName == "J" || opName == "JEQ" || opName == "JGT" || opName == "JLT" || opName == "JSUB") {
        targetAddress &= (nixbpe[5] ? 0x000FFFFF:0x000FFF);
    }
    
    if (nixbpe[0] == nixbpe[1]) {   // simple addressing
        sicStream << setw(8) << left << opName;
        lisStream << setw(8) << left << opName;
        
        for (int i = 0; i < symValues.size(); i++) { //insert symbol name
            if (targetAddress == symValues[i] && opName != "RSUB") {
                sicStream << setw(9) << left << symNames[i] + (nixbpe[2] ? ",X":"") << endl;
                lisStream << setw(9) << left << symNames[i] + (nixbpe[2] ? ",X":"");
                break;
            }
        }
        if (opName == "RSUB") {
            sicStream << endl;
            lisStream << "         ";
        }
    }
    else if (nixbpe[0]) {   //indirect addressing
        sicStream << setw(7) << left << opName << "@";
        lisStream << setw(7) << left << opName << "@";
        for (int i = 0; i < symValues.size(); i++) { //insert symbol name
            if (targetAddress == symValues[i] && opName != "RSUB") {
                sicStream << setw(9) << left << symNames[i] + (nixbpe[2] ? ",X":"") << endl;
                lisStream << setw(9) << left << symNames[i] + (nixbpe[2] ? ",X":"");
                break;
            }
        }
    }
    else {                  //immediate addressing`
        sicStream << setw(7) << left << opName << "#";
        lisStream << setw(7) << left << opName << "#";
        if (!nixbpe[5]) {
            sicStream << targetAddress << endl;
            lisStream << setw(9) << targetAddress;
        }
    }
    
    if (opName == "LDB") {
        baseAddress = targetAddress;
        for (int i = 0; i < symValues.size(); i++) { //check if symbol name should be inserted
            if (targetAddress == symValues[i]) {
                sicStream << setw(10) << left << symNames[i] << endl;
                sicStream << setw(17) << right << "BASE    " << symNames[i] << endl;
                lisStream << setw(9) << left << symNames[i];
                lisStream << setw(2*(3+nixbpe[5])) << setfill('0') << instruction << setfill(' ') << endl;
                lisStream << setfill('0') << setw(4) << right << currentAddress << setfill(' ') << "  ";
                lisStream << setw(17) << right << "BASE    " << symNames[i] << endl;
                return (3+nixbpe[5]);
            }
        }
    }
    lisStream << right << setfill('0') << setw(2*(3+nixbpe[5])) << instruction << setfill(' ') << endl;
    return (3+nixbpe[5]);
}

int Dasm::instructionAnalyzer(int row, int current){
    OpCode code = *new OpCode;
    int opCode = (int)strtol(objStorage[row].substr(current, 2).c_str(), NULL, 16);
    int instructionLength = code.getOpFormat(opCode);
    lisStream << setfill('0') << setw(4) << right << currentAddress << setfill(' ') << "  ";     //print current address in listing file
    switch (instructionLength) {
        case 1:
            analyzeFormat1(code, opCode, row, current);
            break;
        case 2:
            analyzeFormat2(code, opCode, row, current);
            break;
        case 3:
            instructionLength = analyzeFormat3(code, opCode, row, current);
            break;
        default:
            break;
    }
    return (instructionLength * 2);
}

void Dasm::headerRecordAnalyzer(int row) {
    string finalLine;
    string progName = objStorage[row].substr(1, 6);
    stringstream ss;
    unsigned int progStartAddress = currentAddress = (unsigned int)strtol(objStorage[row].substr(7, 6).c_str(), NULL, 16);
    progLength = (unsigned int)strtol(objStorage[row].substr(13, 6).c_str(), NULL, 16);
    ss << progStartAddress;
    string address = ss.str();
    sicStream << setw(9) << left << progName << "START   " << address <<endl;
    lisStream << setbase(16) << uppercase << setw(4) << setfill('0') << currentAddress << setfill(' ') << "  ";
    lisStream << setw(9) << left << progName << "START   " << address <<endl;
}

void Dasm::textRecordAnalyzer(int row) {
    int textLength = (int)strtol(objStorage[row].substr(7, 2).c_str(), NULL, 16);
    int current = 9;
    while (current < (2 * textLength + 9)) {
        int objSize = instructionAnalyzer(row, current);
        currentAddress += (objSize/2);
        current += objSize;
    }
    for (int i = 0; i < symValues.size(); i++) { //check for assembler directives
        if (currentAddress <= symValues[i]) {    //symbol was not used in program, use "RESW" or "RESB" to allocate memory
            lisStream << setfill('0') << setw(4) << right << currentAddress << setfill(' ') << "  ";
            if ((currentAddress % 3) == 0) {  // if divisible by 3, reserve word
                sicStream << setw(8) << left << symNames[i] << " RESW    ";
                lisStream << setw(8) << left << symNames[i] << " RESW    ";
                if (i+1 < symValues.size()) {
                    sicStream << setw(8) << left << (symValues[i+1]-symValues[i])/3 << endl;
                    lisStream << setbase(10) << setw(8) << left << (symValues[i+1]-symValues[i])/3 << setbase(16) << endl;
                    currentAddress +=(symValues[i+1]-symValues[i]);
                }
                else {
                    sicStream << setw(8) << left << (progLength-symValues[i])/3 << endl;
                    lisStream << setbase(10) << setw(8) << left << (progLength-symValues[i])/3 << setbase(16) << endl;
                    currentAddress += (progLength-symValues[i]);
                }
            }
            else {
                sicStream << setw(8) << left << symNames[i] << " RESB    ";
                lisStream << setw(8) << left << symNames[i] << " RESB    ";
                if (i+1 < symValues.size()) {
                    sicStream << setw(8) << left << (symValues[i+1]-symValues[i]) << endl;
                    lisStream << setbase(10) << setw(8) << left << (symValues[i+1]-symValues[i]) << setbase(16) << endl;
                    currentAddress += (symValues[i+1]-symValues[i])/3;
                }
                else {
                    sicStream << setw(8) << left << (progLength-symValues[i]) << endl;
                    lisStream << setbase(10) << setw(8) << left << (progLength-symValues[i]) << setbase(16) << endl;
                    currentAddress += (progLength-symValues[i])/3;
                }
            }
        }
    }
}

void Dasm::modifyRecordAnalyzer(int row) {
    unsigned int modAddress = (unsigned int)strtol(objStorage[row].substr(1, 6).c_str(), NULL, 16);
    int modLength = (int)strtol(objStorage[row].substr(7, 2).c_str(), NULL, 16);
    int i = 0;
    unsigned int address = 0;
    while (objStorage[i][0] != 'T') {   //find the first text record
        i++;
    }
    address = (unsigned int)strtol(objStorage[i].substr(1, 6).c_str(), NULL, 16);  //store text start address
    
    while (address < modLength) {       //find text record that contains the address to modify
        address += (unsigned int)strtol(objStorage[i].substr(7, 2).c_str(), NULL, 16);
        i++;
    }
    i--;
    address -= (unsigned int)strtol(objStorage[i].substr(7, 2).c_str(), NULL, 16);  //subtract the last text length that was added
    int position = 2 * (modAddress - address) + 10;
    objStorage[i][position] += progLength;
}

void Dasm::endRecordAnalyzer(int row) {
    unsigned int endAddress = (unsigned int)strtol(objStorage[row].substr(1, 6).c_str(), NULL, 16);
    for (int i = 0; i < symValues.size(); i++) //check the symbol table for address of first instruction
        if (endAddress == symValues[i]) {
            sicStream << "         " << setw(8) << left << "END" << symNames[i] << endl;
            lisStream << "               " << setw(8) << left << "END" << symNames[i] << endl;
            break;
        }
}

void Dasm::disassemble() {
    for (int i = 0; i < objStorage.size(); i++) {
        switch (objStorage[i][0]) {
            case 'H':
                headerRecordAnalyzer(i);
                break;
            case 'T':
                textRecordAnalyzer(i);
                break;
            case 'M':
                modifyRecordAnalyzer(i);
                break;
            case 'E':
                endRecordAnalyzer(i);
                break;
            default:
                break;
        }
    }
}

