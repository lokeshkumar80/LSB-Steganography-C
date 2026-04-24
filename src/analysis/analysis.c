#include <stdio.h>
#include <math.h>
#include "stego.h"

void lsb_analysis(const char *file){
    FILE *f=fopen(file,"rb");
    fseek(f,54,SEEK_SET);

    int z=0,o=0; unsigned char b;
    while(fread(&b,1,1,f)){
        if(get_lsb(b)) o++; else z++;
    }
    printf("0:%d 1:%d\n",z,o);
    fclose(f);
}

void chi_square_analysis(const char *file){
    FILE *f=fopen(file,"rb");
    fseek(f,54,SEEK_SET);

    int freq[2]={0}; unsigned char b;
    while(fread(&b,1,1,f))
        freq[get_lsb(b)]++;

    double e=(freq[0]+freq[1])/2.0;
    double chi=pow(freq[0]-e,2)/e + pow(freq[1]-e,2)/e;

    printf("Chi-square: %f\n",chi);
    fclose(f);
}
