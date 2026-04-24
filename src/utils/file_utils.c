#include "stego.h"
long get_file_size(FILE *f){
    fseek(f,0,SEEK_END);
    long s=ftell(f);
    rewind(f);
    return s;
}
