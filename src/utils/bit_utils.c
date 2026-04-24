#include "stego.h"
unsigned char set_lsb(unsigned char byte, int bit){ return (byte & 0xFE) | bit; }
int get_lsb(unsigned char byte){ return byte & 1; }
