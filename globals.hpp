#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

#define DEBUG

//#define NUM_CHAR (1)
//#define NUM_CHAR (8)
#define NUM_CHAR (1024*512)

// Frame number
#define FRAME_NUM 22

// length of LFSR stored as bitmask
#define LFSR1_BITMASK 0x0007FFFF  // 19 bit LFSR 
#define LFSR2_BITMASK 0x003FFFFF  // 22 bit LFSR
#define LFSR3_BITMASK 0x007FFFFF  // 23 bit LFSR

// conditional clocking bits of LFSR
#define LFSR1_CLK_BITMASK 0x00000100  // LFSR_1 clocking bit - 8
#define LFSR2_CLK_BITMASK 0x00000400  // LFSR_2 clocking bit - 10
#define LFSR3_CLK_BITMASK 0x00000400  // LFSR_3 clocking bit - 10

// bitmask for feedback function of LFSR
#define LFSR1_TAP_BITMASK 0x00072000  // LFSR_1 tap bits - 18,17,16,13
#define LFSR2_TAP_BITMASK 0x00300000  // LFSR_2 tap bits - 20,21
#define LFSR3_TAP_BITMASK 0x00700080  // LFSR_3 tap bits - 22,21,20,7

// output bit of lfsr
#define LFSR1_OUTPUT_BIT 0x00040000  // LFSR_1 output bit 18 
#define LFSR2_OUTPUT_BIT 0x00200000  // LFSR_2 output bit 21
#define LFSR3_OUTPUT_BIT 0x00400000  // LFSR_3 output bit 23


// bit position tap bits LFSR1
#define LFSR1_TAP_BITP_13 0x0002000
#define LFSR1_TAP_BITP_16 0x0010000
#define LFSR1_TAP_BITP_17 0x0020000
#define LFSR1_TAP_BITP_18 0x0040000

// bit position tap bits LFSR2
#define LFSR2_TAP_BITP_20 0x0100000
#define LFSR2_TAP_BITP_21 0x0200000

// bit position tap bits LFSR3
#define LFSR3_TAP_BITP_7  0x0000080
#define LFSR3_TAP_BITP_20 0x0100000
#define LFSR3_TAP_BITP_21 0x0200000
#define LFSR3_TAP_BITP_22 0x0400000


// XOR operation
#define XOR(x,y) (x ? !y : y)

// XNOR operation
#define XNOR(x,y) (x ? y : !y)

#define LFSR1_WIDTH (19-1)
#define LFSR2_WIDTH (22-1)
#define LFSR3_WIDTH (23-1)

// Clocking bits
#define LFSR1_CLK_BITP 8
#define LFSR2_CLK_BITP 10
#define LFSR3_CLK_BITP 10

// Tap bits LFSR1
#define TAP1_13_BITP 13
#define TAP1_16_BITP 16
#define TAP1_17_BITP 17
#define TAP1_18_BITP 18

// Tap bits LFSR2
#define TAP2_20_BITP 20
#define TAP2_21_BITP 21

// Tap bits LFSR3
#define TAP3_07_BITP 7
#define TAP3_20_BITP 20
#define TAP3_21_BITP 21
#define TAP3_22_BITP 22
