#include <string.h>
#include "stego.h"
// ✅ CORRECT — pass length explicitly
void decrypt(char *data, const char *key, int len) {
    int klen = strlen(key);
    for (int i = 0; i < len; i++) {
        data[i] ^= key[i % klen];
    }
}

void encrypt(char *data, const char *key, int len) {
    int klen = strlen(key);
    for (int i = 0; i < len; i++) {
        data[i] ^= key[i % klen];
    }
}