#!/bin/bash
gcc -std=c99 zero-one.c -o zero-one -lm
./zero-one test.txt
