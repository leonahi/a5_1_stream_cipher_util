#include "globals.hpp"

bool parity(unsigned long reg)
{
    reg ^= reg >> 16;
    reg ^= reg >> 8;
    reg ^= reg >> 4;
    reg ^= reg >> 2;
    reg ^= reg >> 1;
    return reg&1;
}

bool majority(unsigned long LFSR1, unsigned long LFSR2, unsigned long LFSR3)
{
    register unsigned int sum=0;
    sum = parity(LFSR1 & LFSR1_CLK_BIT) + parity(LFSR2 & LFSR2_CLK_BIT) + parity(LFSR3 & LFSR3_CLK_BIT);
    return ((sum >=2) ? 1 : 0);
}

void shift_left_lfsr(unsigned long &reg, unsigned long mask, unsigned long taps)
{
    register unsigned long shifted_bit = reg & taps;
    reg = (reg << 1) & mask;
    reg |= parity(shifted_bit);
}

// Clock all LFSRs conditionaly
void conditional_shift_left_lfsr(unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3)
{
    register bool m=majority(LFSR1, LFSR2, LFSR3);
    if (((LFSR1 & LFSR1_CLK_BIT)!=0) == m) 
        shift_left_lfsr(LFSR1, LFSR1_BITMASK, LFSR1_TAP_BITMASK);
    if (((LFSR2 & LFSR2_CLK_BIT)!=0) == m)
        shift_left_lfsr(LFSR2, LFSR2_BITMASK, LFSR2_TAP_BITMASK);
    if (((LFSR3 & LFSR3_CLK_BIT)!=0) == m)
        shift_left_lfsr(LFSR3, LFSR3_BITMASK, LFSR3_TAP_BITMASK);   
}

// Clock all LFSRs without condition
void clock_all(unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3)
{
    shift_left_lfsr(LFSR1, LFSR1_BITMASK, LFSR1_TAP_BITMASK);
    shift_left_lfsr(LFSR2, LFSR2_BITMASK, LFSR2_TAP_BITMASK);
    shift_left_lfsr(LFSR3, LFSR3_BITMASK, LFSR3_TAP_BITMASK);
}

// Initialization of A5/1 LFSRs
void a5_init(char *key, unsigned long frame_no, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3)
{
    register bool bit;
    
    // Initialize LFSRs to zero
    LFSR1 = 0;
    LFSR2 = 0;
    LFSR3 = 0;
    
    // A5/1 keysetup
    for(register int i=0; i<8; ++i)
    {
        for(register int j=0; j<8; ++j)
        {
            clock_all(LFSR1, LFSR2, LFSR3);
            bit = (key[i] >> j) & 1;
            LFSR1 ^= bit;
            LFSR2 ^= bit;
            LFSR3 ^= bit;
        }
    }
    
    // Load frame number 
    for(register int i=0; i<22; ++i)
    {
        clock_all(LFSR1, LFSR2, LFSR3);
        bit = ((frame_no >> i) & 1);
        LFSR1 ^= bit;
        LFSR2 ^= bit;
        LFSR3 ^= bit;
    }
    
    // Clock for 100 cycle for key mixing
    for(register int i=0; i<100; ++i)
        conditional_shift_left_lfsr(LFSR1, LFSR2, LFSR3);
        
}

bool get_a5_key(unsigned long LFSR1, unsigned long LFSR2, unsigned long LFSR3)
{
    return parity(LFSR1 & LFSR1_OUTPUT_BIT) ^ parity(LFSR2 & LFSR2_OUTPUT_BIT) ^ parity(LFSR3 & LFSR3_OUTPUT_BIT);
}

void generate_keystream(unsigned short &keystream, unsigned long LFSR1, unsigned long LFSR2, unsigned long LFSR3)
{
    register bool bit;
    keystream = 0;
    for(register int i=0; i<16; ++i)
    {
        conditional_shift_left_lfsr(LFSR1, LFSR2, LFSR3);
        bit = get_a5_key(LFSR1, LFSR2, LFSR3);
        keystream = ((keystream << 1)|bit);
        cout << bit << " : "<<  bitset<16>(keystream) << endl;
    }
}
