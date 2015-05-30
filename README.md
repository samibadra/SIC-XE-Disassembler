Copyright 2015 Sami Badra. All Rights Reserved  

Sami Badra  
Genaro Orodio  
Daniel Silva  

CS 530, Spring 2015  
Assignment #2  
FILE: README

##SIC/XE background
SIC/XE - or 'Simplified Instructional Computer/Extra Equipment' - is a hypothetical computer system introduced in the textbook, "System Software: An Introduction to Systems Programming", by Leland Beck.

A photocopy of 'Appendix A' from the original textbook can be found online by following the link below. It is a concise summary explaining the instruction sets and addressing modes for the SIC/XE architecture.

http://cs.iupui.edu/~xkzou/teaching/csci30000/Figures/Page495-499-Appendix-A.pdf

##Description
The objective for this project is to create a program that disassembles object code into assembly code.

The program shall open a SIC XE object file, <filename>.obj and it’s accompanying symbol file, <filename>.sym, disassemble the object code, and generate an XE source file, <filename.sic>, using the disassembled code. The symbol file, <filename>.sym will contain the SYMTAB and LITTAB the assembler generated when assembling the object file.
To run your program, the user shall provide the filename on the command line when starting/running the disassembler:
% dasm <filename>.obj

I have provided some sample files neccessary to run the program in this repository.

##Input
**.obj file:** contains object code (i.e. machine binary/hex).
**.sym file:** contains both a symbol table (A table descriing each symbol in the program: symbol name, memory location, and address flag for each), and a literal table (table describing each literal: literal name, length, and address).

##Output
**.sic file:** contains the original assembly source code which the .obj and .sym files were generated from.

#Instructions
1. TRANSFER: copy all files to the same local directory. (Do not copy 'sample.sic' as this is supposed to be the output that is generated from the program)
2. COMPILE: Simply type 'make' and enter to compile the program using Makefile
3. RUN: Type 'dasm sample.obj' (or any other .obj file if you have your own.)
4. The program will output the assembly code to a .sic file in the same directory where you ran the program.
    
