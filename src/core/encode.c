#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stego.h"

void encode_text(const char *in, const char *out, const char *msg, const char *key) {
    FILE *fin  = fopen(in,  "rb");
    FILE *fout = fopen(out, "wb");

    if (!fin || !fout) {
        printf("File error\n");
        return;
    }

    unsigned char header[54];
    fread(header, 1, 54, fin);

    int pixel_offset = *(int*)&header[10];  // Bug 3 fix: real data offset
    int width    = *(int*)&header[18];
    int height   = *(int*)&header[22];
    int row_size = (width * 3 + 3) & (~3);

    fwrite(header, 1, 54, fout);

    // Copy any extra header bytes (palette, etc.) between byte 54 and pixel_offset
    unsigned char byte;
    for (int i = 54; i < pixel_offset; i++) {
        fread(&byte,  1, 1, fin);
        fwrite(&byte, 1, 1, fout);
    }

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

    int len = strlen(msg);

    // Bug 2 fix: allocate len+1 so encrypt() doesn't overrun
    unsigned char *data = malloc(len + 1);
    memcpy(data, msg, len + 1);
    encrypt((char*)data, key, len);

    int bit_idx = 0;

    // Embed length (32 bits)
    for (int i = 0; i < 32; i++) {
        int bit = (len >> (31 - i)) & 1;
        pixels[bit_idx] = set_lsb(pixels[bit_idx], bit);
        bit_idx++;
    }

    // Embed message bits
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < 8; j++) {
            int bit = (data[i] >> (7 - j)) & 1;
            pixels[bit_idx] = set_lsb(pixels[bit_idx], bit);
            bit_idx++;
        }
    }

    // Write pixels back with padding
    idx = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < row_size; j++) {
            byte = (j < width * 3) ? pixels[idx++] : 0;
            fwrite(&byte, 1, 1, fout);
        }
    }

    printf("BMP Encoded Successfully\n");

    free(pixels);
    free(data);
    fclose(fin);
    fclose(fout);
}
