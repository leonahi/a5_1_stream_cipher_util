#include "globals.hpp"

unsigned long LFSR1, LFSR2, LFSR3;

extern bool parity(unsigned long reg);
extern void shift_left_lfsr(unsigned long &reg, unsigned long mask, unsigned long taps);
extern bool majority(unsigned long LFSR1, unsigned long LFSR2, unsigned long LFSR3);
extern void conditional_shift_left_lfsr(unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void a5_init(char *key, unsigned long frame, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void generate_keystream_32(unsigned long &keystream, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void generate_keystream_8(unsigned char &keystream, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void encrypt_file(char *plaintext_filename, char *ciphertext_filename, char *key, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void decrypt_file(char *ciphertext_filename, char *key, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);

int main(int argc, char* argv[])
{
    clock_t start, end;
    double total_t;
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
    
    encrypt_file(argv[1], argv[2], key, LFSR1, LFSR2, LFSR3);
    decrypt_file(argv[2], key, LFSR1, LFSR2, LFSR3);
    
    return 0;
}