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