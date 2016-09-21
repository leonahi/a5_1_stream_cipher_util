#include "globals.hpp"

unsigned long LFSR1, LFSR2, LFSR3;

/*
extern bool parity(unsigned long reg);
*/
extern void shift_left_lfsr(unsigned long &reg, unsigned long mask, unsigned long taps, unsigned short int lfsr_no);
extern bool parity_8(unsigned char reg);
extern bool parity_2(unsigned char reg);
extern bool majority(unsigned long LFSR1, unsigned long LFSR2, unsigned long LFSR3);
extern void conditional_shift_left_lfsr(unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void a5_init(char *key, unsigned long frame, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void generate_keystream_32(unsigned long &keystream, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void generate_keystream_8(unsigned char &keystream, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void encrypt_file(char *plaintext_filename, char *ciphertext_filename, char *key, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void decrypt_file(char *ciphertext_filename, char *key, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);

int main(int argc, char* argv[])
{
    unsigned long LFSR1, LFSR2, LFSR3;
    char key[8];
    
    for(int i=0; i<8; ++i)
        key[i] = argv[2][i];
    
    if(argc != 4)
    {
        cout << "Error: Input file or passphrase not found"<<endl;
        cout << "Usage: ./a5 input_filename output_filename passphrase" << endl;
        exit(1);
    }
    /*
    LFSR1 =0xFFFFFFFF;
    LFSR2 =0xFFFFFFFF;
    LFSR3 =0xFFFFFFFF;
    cout << "LFSR1 : " << bitset<32>(LFSR1 & LFSR1_BITMASK) << endl;
    cout << "LFSR2 : " << bitset<32>(LFSR2 & LFSR2_BITMASK) << endl;
    cout << "LFSR3 : " << bitset<32>(LFSR3 & LFSR3_BITMASK) << endl;
    
    cout << "majority : " << majority(LFSR1, LFSR2, LFSR3) << endl;
    */
    /*
    shift_left_lfsr(LFSR1, LFSR1_BITMASK, LFSR1_TAP_BITMASK, 1);
    shift_left_lfsr(LFSR2, LFSR2_BITMASK, LFSR2_TAP_BITMASK, 2);
    shift_left_lfsr(LFSR3, LFSR3_BITMASK, LFSR3_TAP_BITMASK, 3);
    cout << bitset<8>(parity_2(0x03)) << endl;
    */
    /*
    LFSR1 =0xFFFFAAAA;
    LFSR2 =0xFFFFAAAA;
    LFSR3 =0xFFFFAAAA;
    cout << "LFSR2 : " <<  bitset<32>(LFSR2) << endl;
    //shift_left_lfsr(LFSR1, LFSR1_BITMASK, LFSR1_TAP_BITMASK, 1);
    //shift_left_lfsr(LFSR2, LFSR2_BITMASK, LFSR2_TAP_BITMASK, 2);
    shift_left_lfsr(LFSR3, LFSR3_BITMASK, LFSR3_TAP_BITMASK, 3);
    */
    encrypt_file(argv[1], argv[2], key, LFSR1, LFSR2, LFSR3);
    //decrypt_file(argv[2], key, LFSR1, LFSR2, LFSR3);
    
    /*
    unsigned int num=10;
    if (num == 10)
        cout << "if - equal to 10 : " << num << endl;
    if (num == 10)
        cout << "else if - equal to 10 : " << num << endl;
    else
        cout << "not equal to 10 : " << num << endl;
    */
    
    return 0;
}