# Architecture

## Key Challenges

1. BMP Row Padding
   - Each row aligned to 4 bytes
   - Caused bit misalignment during decoding

2. Encryption Side Effects
   - XOR introduced null bytes
   - Required binary-safe handling

## Solutions

- Linear pixel buffer approach
- Explicit bit indexing
- Unsigned char usage for correctness