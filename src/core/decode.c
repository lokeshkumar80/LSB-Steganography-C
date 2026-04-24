#include <stdio.h>
#include <stdlib.h>
#include "stego.h"

void decode_text(const char *in, const char *key) {
    FILE *fin = fopen(in, "rb");

    if (!fin) {
        printf("File error\n");
        return;
    }

    unsigned char header[54];
    fread(header, 1, 54, fin);

    int pixel_offset = *(int*)&header[10];  // Bug 3 fix: real data offset
    int width    = *(int*)&header[18];
    int height   = *(int*)&header[22];
    int row_size = (width * 3 + 3) & (~3);

    // Skip extra header bytes
    unsigned char byte;
    for (int i = 54; i < pixel_offset; i++)
        fread(&byte, 1, 1, fin);

    int pixel_bytes = width * height * 3;
    unsigned char *pixels = malloc(pixel_bytes);

    int idx = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < row_size; j++) {
            fread(&byte, 1, 1, fin);
            if (j < width * 3)
                pixels[idx++] = byte;
        }
    }

    fclose(fin);

    // Extract length
    int len = 0;
    for (int i = 0; i < 32; i++)
        len = (len << 1) | get_lsb(pixels[i]);

    printf("Extracted length: %d\n", len);

    unsigned char *msg = malloc(len + 1);
    int bit_idx = 32;

    for (int i = 0; i < len; i++) {
        unsigned char ch = 0;
        for (int j = 0; j < 8; j++)
            ch = (ch << 1) | get_lsb(pixels[bit_idx++]);
        msg[i] = ch;
    }

    msg[len] = '\0';
    decrypt((char*)msg, key, len);

    printf("Decoded: %s\n", msg);

    free(msg);
    free(pixels);
}

