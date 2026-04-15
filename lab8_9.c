#include <stdio.h>
#include <stdlib.h>
#include "lab8header.h"

extern char *mem;
extern int registers[32];

// Define the PC register only once
unsigned int PCRegister = 0;

 // Fetch the  32-bit instruction

unsigned int CPU_fetchCode(char *mem, int codeOffset) {
    unsigned int instruction = 0;

    instruction = ((unsigned char)mem[codeOffset] << 24) |
                  ((unsigned char)mem[codeOffset + 1] << 16) |
                  ((unsigned char)mem[codeOffset + 2] << 8)  |
                  ((unsigned char)mem[codeOffset + 3]);

    return instruction;
}

 // Decode instruction fields

unsigned char CPU_Decode(unsigned int machineCode) {

    unsigned int opcode = (machineCode >> 26) & 0x3F;
    unsigned int rs     = (machineCode >> 21) & 0x1F;
    unsigned int rt     = (machineCode >> 16) & 0x1F;
    unsigned int rd     = (machineCode >> 11) & 0x1F;
    unsigned int shamt  = (machineCode >> 6)  & 0x1F;
    unsigned int funct  = machineCode & 0x3F;
    unsigned int imm    = machineCode & 0xFFFF;
    unsigned int addr   = machineCode & 0x03FFFFFF;

    // Print the statements
    printf("\n--- Instruction Decode ---\n");
    printf("Machine Code: %08X\n", machineCode);
    printf("Opcode: %02X\n", opcode);
    printf("rs: %d, rt: %d, rd: %d\n", rs, rt, rd);
    printf("shamt: %d, funct: %02X\n", shamt, funct);
    printf("Immediate: %04X\n", imm);
    printf("Address: %08X\n", addr);

    return (unsigned char)opcode;
}

  //Print register file

void printRegisterFiles() {
    printf("\n--- Register File Dump ---\n");

    for (int i = 0; i < 32; i++) {
        printf("R%02d: %d\t", i, registers[i]);

        if ((i + 1) % 4 == 0)
            printf("\n");
    } }


 //Print first 64 bytes of memory

void printDataMemoryDump() {
    printf("\n--- Data Memory Dump (First 64 Bytes) ---\n");

    for (int i = 0; i < 64; i++) {
        printf("%02X ", (unsigned char)mem[i]);

        if ((i + 1) % 16 == 0)
            printf("\n");
    } }


 // Execution stage

void CPU_Execution(unsigned char opcode, unsigned int machineCode, char *mem) {
    printf("\n--- Execution Stage ---\n");
    printf("Executing Opcode: %02X\n", opcode);
}


  //Main CPU cycle

void CPU(char *mem) {

    unsigned int instruction;
    unsigned char opcode;

    printf("\n================ CPU Cycle ================\n");

    // fetch the memory
    instruction = CPU_fetchCode(mem, PCRegister);

    // decode the memory
    opcode = CPU_Decode(instruction);

    // execute the memory
    CPU_Execution(opcode, instruction, mem);

    // print out the memory and the state of it
    printRegisterFiles();
    printDataMemoryDump();

    // Increment the  PC register
    PCRegister += 4;
}
