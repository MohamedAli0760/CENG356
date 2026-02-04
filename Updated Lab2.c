/*
 ============================================================================
 Name        : Lab2.c
 Author      : Mohamed ALI
 Version     :
 Copyright   : Copyright 2026
 Description : Signed number and unsigned numbers, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 32
#define number1 "11000001010010000000000000000000"
#define number2 "01000001010101000000000000000000"
void convert_binary_to_signed(const char *binary);
void convert_binary_to_float(const char *binary);

// Define the user interface menu as a string
char *menu = "\n" \
             "===================================================================\n" \
             "************Please select the following options********************\n" \
             " * 1. Binary number to signed decimal number conversion.(Lab 2) *\n" \
             " * 2. Binary number to Floating number conversion (Lab 2)       *\n" \
             " *******************************************************************\n" \
             " * e. To Exit, Type 'e'                                         *\n" \
             " *******************************************************************\n";

int main(void) {
    char options;        // Variable to store user menu options
    char inputs[33] = {0}; // Buffer to store the binary string input

    do {
        puts(menu);      // Display the menu from the console
        fflush(stdin);   // Clear the input buffer
        options = getchar(); // Read  single character from the user

        switch (options) {
            case '1': // User chose an 8-bit signed conversion
                puts("Please input your 8-bit BINARY number:");
                scanf("%s", inputs);            // Read string input from user
                convert_binary_to_signed(inputs); // Call back signed conversion function
                continue;                       // Return to start of loop
            case '2': // User chose 32-bit float conversion
                puts("Please input your 32-bit floating point number in binary:");
                scanf("%s", inputs);            // Read a 32-character string
                convert_binary_to_float(inputs); // Call float conversion function
                continue;                       // Return to start of loop
            case 'e': // User chose to exit
                puts("Code finished, exit now");
                return EXIT_SUCCESS;            // Terminate program
            default: // User entered an invalid character
                puts("Not a valid entry, please try again.");
                continue;                       // Return to start of loop
        }}
         while (1); // Infinite loop dontinues until 'e' is pressed, program then terminates
}

/**
 * Option 1: 8-bit Two's Complement conversion
 */
void convert_binary_to_signed(const char *binary) {
    int val = 0;              // Initialize integer to store decimal solutions
    int len = strlen(binary); //  length of the input string

    // Loop through each character in the string to calculate unsigned value
    for (int i = 0; i < len; i++) {
        if (binary[i] == '1') {

            val += pow(2, len - 1 - i);
        } }

    // Check if the number should be treated as negative (8-bit signed logic)
    // If length is 8 and MSB (index 0) is '1', subtract 2^8 (256)
    if (len == 8 && binary[0] == '1') {
        val = val - 256;
    }

    printf("Signed Decimal Output: %d\n", val); // Print  final signed result
}

/**
 * Option 2: 32-bit IEEE 754 Floating Point conversion
 */
void convert_binary_to_float(const char *binary) {
    // Validate the input is  32 bits
    if (strlen(binary) != 32) {
        puts("Error: Requires a 32-bit string.");
        return; // Exit function if input is invalid ( Not 32 bit string)
    }

    // Determine the Sign bit
    // If '1', multiplier is -1. If '0', multiplier is 1.
    int sign = (binary[0] == '1') ? -1 : 1;

    //  Calculate the Exponent (bits 1 through 8)
    int exponent = 0;
    for (int i = 1; i <= 8; i++) {
        if (binary[i] == '1') {
            // Bits 1-8 represent 2^7 down to 2^0
            exponent += pow(2, 8 - i);
        } }
    // Subtract the IEEE 754 bias (127) for single precision
    int actual_exponent = exponent - 127;

    //  Calculate the Mantissa/Fraction (bits 9 through 31)
    float mantissa = 1.0; // Start with the implicit leading 1
    for (int i = 9; i < 32; i++) {
        if (binary[i] == '1') {
            // Each bit represents 2 to the power of negative (position from decimal)
            mantissa += pow(2, -(i - 8));
        } }
    float result = sign * mantissa * pow(2, actual_exponent);

    printf("Floating Point Output: %f\n", result); // Print result as a float
}