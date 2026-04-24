#include <stdio.h>
#include <string.h>
#include "stego.h"

int main(int argc,char *argv[]){
    if(argc<2){ printf("Usage\n"); return 1; }

    if(strcmp(argv[1],"encode")==0)
        encode_text(argv[2],argv[3],argv[4],argv[5]);

    else if(strcmp(argv[1],"decode")==0)
        decode_text(argv[2],argv[3]);

    else if(strcmp(argv[1],"analyze")==0){
        lsb_analysis(argv[2]);
        chi_square_analysis(argv[2]);
    }

    return 0;
}
