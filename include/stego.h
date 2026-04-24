#ifndef STEGO_H
#define STEGO_H
#include <stdio.h>

void encode_text(const char*, const char*, const char*, const char*);
void decode_text(const char*, const char*);
void encode_png(const char*, const char*, const char*, const char*);
void decode_png(const char*, const char*);

unsigned char set_lsb(unsigned char, int);
int get_lsb(unsigned char);
long get_file_size(FILE*);

void encrypt(char*, const char*, int);
void decrypt(char*, const char*, int);

void lsb_analysis(const char*);
void chi_square_analysis(const char*);

unsigned char* read_png(const char*, int*, int*);
void write_png(const char*, unsigned char*, int, int);

#endif
