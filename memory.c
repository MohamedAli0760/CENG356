/*
 ============================================================================
 Name        : memory.c
 Author      : Austin Tian
 Revised by  : Mohamed Ali
 Version     : 1.0
 Copyright   : Copyright 2026
 Description : Lab 6 - Memory Control Interface
 ============================================================================
 */

#include "header.h"

// Menu for the interface to be tested
char *menu =    "\n" \
                " ***********Please select the following options**********************\n" \
                " * This is the memory operation menu (Lab 6)                     *\n" \
                " ********************************************************************\n" \
                " * 1. Write a double-word (32-bit) to the memory                 *\n"  \
                " ********************************************************************\n" \
                " * 2. Read a byte (8-bit) data from the memory                   *\n" \
                " * 3. Read a double-word (32-bit) data from the memory           *\n" \
                " ********************************************************************\n" \
                " * 4. Generate a memory dump from any memory location            *\n" \
                " ********************************************************************\n" \
                " * e. To Exit, Type 'e'  or 'E'                                  *\n" \
                " ********************************************************************\n";


// Helper to generate a random number between 0x00 and 0xFF
unsigned char rand_generator()
{
    return rand() % 256;
}

// Standard cleanup to prevent memory leaks
void free_memory(char *base_address)
{
    free(base_address);
    return;
}

//  Fill in bytes with numbers to be randomized
char *init_memory()
{
    // Allocate 1M bytes
    char *mem = (char *)malloc(MEM_SIZE);

    if (mem == NULL) {
        printf("System  to allocate memory failed.\n");
        exit(1);
    }

    // Initialize memory with random values
    for (int i = 0; i < MEM_SIZE; i++) {
        mem[i] = (char)rand_generator();
    }

    return mem;
}

//  Write 32-bit double-word to "base_address + offset"
void write_dword(const char *base_address, const int offset, const unsigned int dword_data) {
    // Cast  address to an unsigned int pointer to write 4 bytes
    unsigned int *ptr = (unsigned int *)(base_address + offset);
    *ptr = dword_data;
}

// Read a byte (8-bit) from the specified address
unsigned char read_byte(const char *base_address, const int offset) {
    unsigned char val = (unsigned char)base_address[offset];
    printf("Byte at offset 0x%X: 0x%02X\n", offset, val);
    return val;
}


//  Read  double-word (32-bit) from the specified address
unsigned int read_dword(const char *base_address, const int offset) {
    unsigned int val = *(unsigned int *)(base_address + offset);
    printf("Double-word at offset 0x%X: 0x%08X\n", offset, val);
    return val;
}

// Generate memory dump with HEX and ASCII to complete the dump
void memory_dump(const char *base_address, const int offset, unsigned int dumpsize) {

    // Make sure the dump size meets the lowest requirement
    if (dumpsize < MIN_DUMP_SIZE || dumpsize > MEM_SIZE)
        dumpsize = MIN_DUMP_SIZE;

    printf("\n");
    for (unsigned int i = 0; i < dumpsize; i += DUMP_LINE) {
        // Print the current absolute memory address in HEX
        printf("%p: ", (void*)(base_address + offset + i));

        // Display 16 bytes in HEX 
        for (int j = 0; j < DUMP_LINE; j++) {
            printf("%02X ", (unsigned char)base_address[offset + i + j]);
        }

        printf("  --  ");

        // Display the ASCII
        for (int j = 0; j < DUMP_LINE; j++) {
            unsigned char c = (unsigned char)base_address[offset + i + j];
            //  show characters in the readable range of 0x20 to 0x7E
            if (c >= 0x20 && c <= 0x7E) {
                printf("%c ", c);
            } else {
                printf(". ");
            } }
        printf("\n");
    } }


// Main logic
void setup_memory()
{
    // Initialize the memory, the dump sizze and the double-word
    char *mem = init_memory();
    char options = 0;
    unsigned int offset, dumpsize;
    char tempchar;
    unsigned int dword_data;

    do {
        // Prevent  re-printing on newline characters on the menu
        if (options != 0x0a)
        {
            puts(menu);
            printf ("\nThe base address of your memory is: %p (HEX)\n", (void*)mem);
            puts("Please make a selection:");
        }

        options = getchar();

        switch (options)
        {
            // cases to be done during the lab demonstration
            case '1': // Write a Double-Word into the prompt
                puts("Please input your memory's offset address (in HEX):");
                scanf("%x", &offset);
                puts("Please input your DOUBLE WORD data to be written (in HEX):");
                scanf("%x", &dword_data);
                write_dword(mem, offset, dword_data);
                continue;
            case '2': // Read Byte into the prompt
                puts("Please input your memory's offset address (in HEX):");
                scanf("%x", &offset);
                read_byte(mem, offset);
                continue;
            case '3': // Read Double-Word into the prompt
                puts("Please input your memory's offset address (in HEX):");
                scanf("%x", &offset);
                read_dword(mem, offset);
                continue;
            case '4': // Memory Dump to be completed
                puts("Please input your memory's offset address (in HEX, should be a multiple of 0x10h):");
                scanf("%x", &offset);
                puts("Please input the size of the memory to be dumped (between 256 and 1M ):");
                scanf("%u", &dumpsize);
                memory_dump(mem, offset, dumpsize);
                continue;
            case 'e': // type lower e to exit
            case 'E': // type upper e to exit
                puts("Code finished, press any key to exit");
                free_memory(mem);
                // Clear buffer and wait for user to return to main screen
                while ((tempchar = getchar()) != '\n' && tempchar != EOF);
                tempchar = getchar();
                return;
            default:
                continue;
        }  }
 while (1);
}


