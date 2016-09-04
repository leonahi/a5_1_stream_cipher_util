#include "globals.hpp"

unsigned long LFSR1, LFSR2, LFSR3;

extern bool parity(unsigned long reg);
extern void shift_left_lfsr(unsigned long &reg, unsigned long mask, unsigned long taps);
extern bool majority(unsigned long LFSR1, unsigned long LFSR2, unsigned long LFSR3);
extern void conditional_shift_left_lfsr(unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void a5_init(char *key, unsigned long frame, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void generate_keystream(unsigned short &keystream, unsigned long LFSR1, unsigned long LFSR2, unsigned long LFSR3);

int main(int argc, char* argv[])
{
    unsigned long LFSR1, LFSR2, LFSR3;
    char key[8] = {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'};
    unsigned long frame_no = 22;
    unsigned short keystream=0;
    
    cout << parity(7) << endl;
    
    LFSR1 = 0xAAFFAAAF;
    LFSR2 = 0xAAFAAAAF;
    LFSR3 = 0xAAFAAAAF;
    
    /*
    cout << "LFSR1 : " << bitset<32>(LFSR1) << endl;
    shift_left_lfsr(LFSR1, LFSR1_BITMASK, LFSR1_TAP_BITMASK);
    cout << "LFSR1 : " << bitset<32>(LFSR1) << endl;
    */
    /*
    cout << endl;
    cout << "LFSR1 : " << bitset<32>(LFSR1 & LFSR1_BITMASK) << endl;
    cout << "LFSR2 : " << bitset<32>(LFSR2 & LFSR2_BITMASK) << endl;
    cout << "LFSR3 : " << bitset<32>(LFSR3 & LFSR3_BITMASK) << endl;
    cout << endl;
    
    conditional_shift_left_lfsr(LFSR1, LFSR2, LFSR3);
    
    cout << "LFSR1 : " << bitset<32>(LFSR1) << endl;
    cout << "LFSR2 : " << bitset<32>(LFSR2) << endl;
    cout << "LFSR3 : " << bitset<32>(LFSR3) << endl;
    */
    cout << "key : " << bitset<8>(key[0]) << endl;
    cout << "key : " << bitset<8>((key[0]<<1)) << endl;
    
    a5_init(key, frame_no, LFSR1, LFSR2, LFSR3);
    cout << "LFSR1 : " << bitset<20>(LFSR1 & LFSR1_BITMASK) << endl;
    cout << "LFSR2 : " << bitset<20>(LFSR1 & LFSR1_BITMASK) << endl;
    cout << "LFSR3 : " << bitset<20>(LFSR1 & LFSR1_BITMASK) << endl;
    
    generate_keystream(keystream, LFSR1, LFSR2, LFSR3);
    cout << "keystream : " << bitset<16>(keystream) << endl;
    
    
    return 0;
}