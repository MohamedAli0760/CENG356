/*
 * Lab 7: MIPS Encoding
 * Lab7.c
 * Mohamed Ali
 */

 #include "header.h"
 #include <time.h>
 #include <string.h>


//  DATA SECTION
void setupDataMemory(char* base_address, unsigned int offset, char *datasection, unsigned int numberOfBytes) {
    for (unsigned int i = 0; i < numberOfBytes; i++) {
        base_address[offset + i] = datasection[i];
    } }

// I-TYPE
unsigned int buildIInstruction(unsigned char opcode, unsigned char rs, unsigned char rt, int immediate) {
    unsigned int machineCode = 0;

    machineCode |= (opcode & 0x3F) << 26;
    machineCode |= (rs & 0x1F) << 21;
    machineCode |= (rt & 0x1F) << 16;
    machineCode |= (immediate & 0xFFFF);

    return machineCode;
}

// R-TYPE
unsigned int buildRInstruction(unsigned char opcode, unsigned char rs, unsigned char rt,
                               unsigned char rd, unsigned char shamt, unsigned char funct) {

    unsigned int machineCode = 0;

    machineCode |= (opcode & 0x3F) << 26; // always 0
    machineCode |= (rs & 0x1F) << 21;
    machineCode |= (rt & 0x1F) << 16;
    machineCode |= (rd & 0x1F) << 11;
    machineCode |= (shamt & 0x1F) << 6;
    machineCode |= (funct & 0x3F);

    return machineCode;
}

// J-TYPE
unsigned int buildJInstruction(unsigned char opcode, int address) {
    unsigned int machineCode = 0;

    machineCode |= (opcode & 0x3F) << 26;
    machineCode |= (address & 0x03FFFFFF);

    return machineCode;
}

// INSTRUCTION MEMORY
void setupInstructionMemory(char* base_memory_address, int codeOffset, MIPS_Instruction *instructionStorage) {

    int i = 0;
    unsigned int machineCode = 0;

    while (strcmp(instructionStorage[i].instruction, "END") != 0) {

        //  I-TYPE
        if (strcmp(instructionStorage[i].instruction, "lb") == 0) {
            machineCode = buildIInstruction(0x20, instructionStorage[i].rs,
                                           instructionStorage[i].rt,
                                           instructionStorage[i].immediate);
        }
        else if (strcmp(instructionStorage[i].instruction, "lw") == 0) {
            machineCode = buildIInstruction(0x23, instructionStorage[i].rs,
                                           instructionStorage[i].rt,
                                           instructionStorage[i].immediate);
        }
        else if (strcmp(instructionStorage[i].instruction, "sw") == 0) {
            machineCode = buildIInstruction(0x2B, instructionStorage[i].rs,
                                           instructionStorage[i].rt,
                                           instructionStorage[i].immediate);
        }
        else if (strcmp(instructionStorage[i].instruction, "addi") == 0) {
            machineCode = buildIInstruction(0x08, instructionStorage[i].rs,
                                           instructionStorage[i].rt,
                                           instructionStorage[i].immediate);
        }
        else if (strcmp(instructionStorage[i].instruction, "bge") == 0) {
            machineCode = buildIInstruction(0x01, instructionStorage[i].rs,
                                           instructionStorage[i].rt,
                                           instructionStorage[i].immediate);
        }

        //  R-TYPE
        else if (strcmp(instructionStorage[i].instruction, "add") == 0) {
            machineCode = buildRInstruction(0x00, instructionStorage[i].rs,
                                           instructionStorage[i].rt,
                                           instructionStorage[i].rd,
                                           0, 0x20);
        }

        // J-TYPE
        else if (strcmp(instructionStorage[i].instruction, "j") == 0) {
            machineCode = buildJInstruction(0x02, instructionStorage[i].address);
        }

        //  SYSTEM CALL
        else if (strcmp(instructionStorage[i].instruction, "syscall") == 0) {
            machineCode = 0x0000000C;
        }

        // DEFAULT SYSTEM CALL
        else {
            machineCode = 0;
        }

        write_dword(base_memory_address, codeOffset + (i * 4), machineCode);
        i++;
    } }

// LOAD THE MEMORY DUMP INTO THE MACHINE
void loadCodeToMem(char *mem) {

    setupDataMemory(mem, DATASECTION, Data_storage, totalDataByte);
    setupInstructionMemory(mem, CODESECTION, Instruction_storage);

    puts("\n---- Data Section ----\n");
    memory_dump(mem, DATASECTION, 256);

    puts("\n---- Code Section ----\n");
    memory_dump(mem, CODESECTION, 256);
}
