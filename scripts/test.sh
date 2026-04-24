#!/bin/bash

echo "Running tests..."

./stego encode test_images/test1.bmp outputs/out.bmp "hello lokesh" key
./stego decode outputs/out.bmp key

./stego encode test_images/test1.bmp outputs/out.bmp "A" key
./stego decode outputs/out.bmp key

echo "Done."