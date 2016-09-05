#include "globals.hpp"

unsigned long LFSR1, LFSR2, LFSR3;

extern bool parity(unsigned long reg);
extern void shift_left_lfsr(unsigned long &reg, unsigned long mask, unsigned long taps);
extern bool majority(unsigned long LFSR1, unsigned long LFSR2, unsigned long LFSR3);
extern void conditional_shift_left_lfsr(unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void a5_init(char *key, unsigned long frame, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void generate_keystream_32(unsigned long &keystream, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);
extern void generate_keystream_8(unsigned char &keystream, unsigned long &LFSR1, unsigned long &LFSR2, unsigned long &LFSR3);

int main(int argc, char* argv[])
{
    clock_t start, end;
    double total_t;
    unsigned long LFSR1, LFSR2, LFSR3;
    char key[8] = {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'};
    unsigned long frame_no = 22;
    unsigned long keystream_32=0;
    
    unsigned long charstream_32=0;
    unsigned long chipher_text_32=0;
    unsigned long num_plain_text_char=0;
    
    unsigned char keystream_8=0;
    unsigned long charstream_8=0;
    unsigned long chipher_text_8=0;
    
    unsigned char *plain_text_buffer;
    plain_text_buffer = new unsigned char[NUM_CHAR];
    
    char file_char;
    //char plain_text_buffer[4];
    
    LFSR1 = 0xAAFFAAAF;
    LFSR2 = 0xAAFAAAAF;
    LFSR3 = 0xAAFAAAAF;
    
    /*
    a5_init(key, frame_no, LFSR1, LFSR2, LFSR3);
    generate_keystream_8(keystream_8, LFSR1, LFSR2, LFSR3);
    return 0;
    */
        
    if(argc != 3)
    {
        cout << "Error: Input file or passphrase not found"<<endl;
        cout << "Usage: ./a5 input_filename passphrase" << endl;
        exit(1);
    }
    ifstream in_file(argv[1]); 
    if(!in_file.is_open())
    {
        cout << endl << "-----------------------------------------------------------------------" << endl;
        cout << "Error: Unable to open input file" << argv[1] << endl;
        cout << endl << "-----------------------------------------------------------------------" << endl;
        exit(1);
    }
    
    fstream out_file;
    out_file.open("ciphertext.txt", fstream::out);
    
    cout << "Starting Encryption..." << endl;
    start = clock();
    
    a5_init(key, frame_no, LFSR1, LFSR2, LFSR3);
    while(!in_file.eof())
    {
        for(int i=0; i<NUM_CHAR; ++i)
        {
            in_file.get(file_char);
            plain_text_buffer[i] = file_char;
            ++num_plain_text_char;
            //cout << "plain_text_buffer : " << bitset<8>(plain_text_buffer[i]) << endl;
            //cout << "file_char         : " << bitset<8>(file_char) << endl;
        }
        for(int i=0; i<NUM_CHAR; ++i)
        {
            generate_keystream_8(keystream_8, LFSR1, LFSR2, LFSR3);
            chipher_text_8 = plain_text_buffer[i] ^ keystream_8;
            //cout << "keystream_8       : " << bitset<8>(keystream_8) << endl;
            //cout << "file_char        : " << bitset<8>(file_char) << endl;
            //cout << "chipher_text_8    : " << bitset<8>(chipher_text_8) << endl;
        }
        /*
        generate_keystream_32(keystream_32, LFSR1, LFSR2, LFSR3);
        chipher_text_32 = keystream_32 ^ charstream_32;
        cout << "charstream_32   : " << bitset<32>(charstream_32) << endl;
        cout << "keystream_32    : " << bitset<32>(keystream_32) << endl;
        cout << "chipher_text_32 : " << bitset<32>(chipher_text_32) << endl;
        */
    }
    
    end = clock();
    cout << "Encryption Done!" << endl;
    total_t = (double)(end-start)/CLOCKS_PER_SEC;
    cout << "Total time for encryption : " << total_t << " seconds" <<endl;
    cout << "Speed in Mbps : " << ((num_plain_text_char*8)/total_t)/1000000 << endl;
    
    cout << "Total number of bits : " << (num_plain_text_char*8) << endl;
    /*
    while(!in_file.eof())
    {
        for(int i=0; i<NUM_CHAR; ++i)
        {
            in_file.get(file_char);
            charstream_32 = ((charstream_32 << 8) | (file_char));
            cout << bitset<8>(file_char) << endl;
        }
        generate_keystream_32(keystream_32, LFSR1, LFSR2, LFSR3);
        chipher_text_32 = keystream_32 ^ charstream_32;
        cout << "charstream_32   : " << bitset<32>(charstream_32) << endl;
        cout << "keystream_32    : " << bitset<32>(keystream_32) << endl;
        cout << "chipher_text_32 : " << bitset<32>(chipher_text_32) << endl;
        ++plain_text_bits_length;
    }
    */
    in_file.close();
    
    out_file.close();
    
    
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
    /*
    cout << "key : " << bitset<8>(key[0]) << endl;
    cout << "key : " << bitset<8>((key[0]<<1)) << endl;
    */
    /*
    a5_init(key, frame_no, LFSR1, LFSR2, LFSR3);
    cout << "LFSR1 : " << bitset<20>(LFSR1 & LFSR1_BITMASK) << endl;
    cout << "LFSR2 : " << bitset<20>(LFSR1 & LFSR1_BITMASK) << endl;
    cout << "LFSR3 : " << bitset<20>(LFSR1 & LFSR1_BITMASK) << endl;
    
    generate_keystream(keystream, LFSR1, LFSR2, LFSR3);
    cout << "keystream : " << bitset<16>(keystream) << endl;
    generate_keystream(keystream, LFSR1, LFSR2, LFSR3);
    cout << "keystream : " << bitset<16>(keystream) << endl;
    */
    
    return 0;
}