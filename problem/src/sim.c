#include <stdint.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#include <ctype.h>
#include "shell.h"

#define MEM_TEXT_START 0x00400000

char* decimalToBinary(uint32_t hex);
char* getSubset(uint32_t number, uint32_t indexes[2]);
uint32_t createMask(uint32_t a, uint32_t b); 
uint8_t compare(char* bits, char* pattern); 

/*
TODO: 
1. write a function to convert hex instruction to binary DONE
2. figure out a way to recognize the opcode (maybe first 11 bits?) 
3. categorize into different standard types
4. write individual functions for handling each type & write massive switch function for each operation
*/

uint32_t fetch()
{
    uint32_t hex_instruction = mem_read_32(MEM_TEXT_START); 
    return hex_instruction; 
}

void decode()
{
    uint32_t decInstruction = fetch(); 
    char* binaryInstruction = decimalToBinary(decInstruction); 
} 

void execute() {

}

void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */
    // fetch(); 
    decode();
    // execute();

}

/*********************** HELPER FUNCTIONS ***************************/

/* Function to convert decimal 32bit value to Binary string value */
char* decimalToBinary(uint32_t hex) {
    int index; 
    char bits[32] = {'0','0','0','0','0','0','0','0'};
    index = 31;
    while ( hex > 0 ) {
        bits[index--] = (hex & 1) + '0';
        hex >>= 1;
    }

    return bits;
}

/* Get bit subset from integer */
char* getSubset(uint32_t number, uint32_t indexes[2]) {
    uint32_t firstIndex, secondIndex;
    // get real indices
    secondIndex = 31 - indexes[0]; // start of subset range is actually reversed
    firstIndex = 31 - indexes[1];
    // make a 32-bit number that has ones in those indices
    uint32_t r, result; 
    char* decimalResult; 
    r = createMask(firstIndex, secondIndex);
    result = r & number;
    decimalResult = decimalToBinary(result); 

    return decimalResult; 
}

/* Compares bits with a specific pattern and returns truth value for control branching*/
uint_fast8_t compare(char* bits, char* pattern) {
    // compare bits to pattern
    if (strcmp(bits, pattern) == 1) {

    } 
    // if same (true) return 1 
    // if not (false) return 0
    return 1; 
}

/* Create a mask with two indexes */ 
uint32_t createMask(uint32_t idx1, uint32_t idx2) {
   uint32_t r = 0;
   for (unsigned i=idx1; i<=idx2; i++)
       r |= 1 << i;

   return r;
}

