# About this program
  
This C program simulates the execution of a program written in a simplified Harvard Architecture Instruction Set Architecture (ISA). The program reads instructions from a file, stores them in memory, and then executes a fetch-execute cycle for each instruction. The simulated machine has an instruction set that includes operations like LOAD, ADD, STORE, SUBTRACT, INPUT, OUTPUT, END, JUMP, and SKIP IF ZERO. During execution, the program updates the machine's state, including the program counter, accumulator, and data memory. The simulation continues until an END instruction is encountered, and the final state of the machine is printed. The program also handles errors, such as file opening issues and unknown opcodes. It provides a basic framework for simulating the behavior of a Harvard Architecture ISA.

# Supported opcodes
-   01: LOAD X - Meaning: A <- DM[X]
-   02: ADD X - Meaning: A <- A + DM[X]
-   03: STORE X - Meaning: DM[X] <- A
-   04: SUB X - Meaning: A <- A - DM[X]
-   05: IN - Meaning: Input value into A
-   06: OUT - Meaning: Output A to screen
-   07: END - Meaning: End of program
-   08: JMP X - Meaning: Jump to memory location X
-   09: SKIPZ - Meaning: Skip next instruction if A is zero

# Assignment
Homework 3

# Author
Nicholas Donofrio

# School
University of Central Florida

# Professor/Class
Euripides Montagne / CGS3269-23Fall 0001

Due: November 28, 2023

# Language
C

# To Compile:
gcc tinyvm.c

# To Execute:
./tinyvm elf.txt > output.txt

