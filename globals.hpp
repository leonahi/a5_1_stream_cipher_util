#include <iostream>
#include <bitset>

using namespace std;

#define DEBUG

// length of LFSR stored as bitmask
#define LFSR1_BITMASK 0x0007FFFF  // 19 bit LFSR 
#define LFSR2_BITMASK 0x003FFFFF  // 22 bit LFSR
#define LFSR3_BITMASK 0x077FFFFF  // 23 bit LFSR

// conditional clocking bits of LFSR
#define LFSR1_CLK_BIT 0x00000100  // LFSR_1 clocking bit 
#define LFSR2_CLK_BIT 0x00000400  // LFSR_2 clocking bit
#define LFSR3_CLK_BIT 0x00000400  // LFSR_3 clocking bit

// bitmask for feedback function of LFSR
#define LFSR1_TAP_BITMASK 0x00072000  // LFSR_1 tap bits 
#define LFSR2_TAP_BITMASK 0x00300000  // LFSR_2 tap bits
#define LFSR3_TAP_BITMASK 0x00700080  // LFSR_3 tap bits

// output bit of lfsr
#define LFSR1_OUTPUT_BIT  0x00040000  // LFSR_1 output bit 18 
#define LFSR2_OUTPUT_BIT  0x00200000  // LFSR_2 output bit 21
#define LFSR3_OUTPUT_BIT  0x00400000  // LFSR_3 output bit 23


// XOR operation
#define XOR(x,y) (x ? !y : y)

// XNOR operation
#define XNOR(x,y) (x ? y : !y)

#define LFSR1_WIDTH 19
#define LFSR2_WIDTH 22
#define LFSR3_WIDTH 23

// Clocking bits
#define CLK_BIT_1 8
#define CLK_BIT_2 10
#define CLK_BIT_3 10

// Tap bits LFSR1
#define TAP1_BIT_13 13
#define TAP1_BIT_16 16
#define TAP1_BIT_17 17
#define TAP1_BIT_18 18

// Tap bits LFSR2
#define TAP2_BIT_20 20
#define TAP2_BIT_21 21

// Tap bits LFSR3
#define TAP2_BIT_07 7
#define TAP2_BIT_20 20
#define TAP2_BIT_21 21
#define TAP2_BIT_22 22