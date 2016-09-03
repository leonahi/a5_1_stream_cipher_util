#include "globals.hpp"

unsigned long LFSR1, LFSR2, LFSR3;

extern bool parity(unsigned long reg);
extern void shift_left_lfsr(unsigned long &reg, unsigned long mask, unsigned long taps);

int main(int argc, char* argv[])
{
    unsigned long LFSR1, LFSR2, LFSR3;
    
    cout << parity(7) << endl;
    
    LFSR1 = 0xAAAAAAAA;
    cout << "LFSR1 : " << bitset<32>(LFSR1) << endl;
    shift_left_lfsr(LFSR1, LFSR1_BITMASK, LFSR1_TAP_BITMASK);
    cout << "LFSR1 : " << bitset<32>(LFSR1) << endl;
    
    
    return 0;
}