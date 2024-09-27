#!/bin/bash

set -xe
CFLAGS="-Wall -Wextra -O3 -std=c11"  

clang -o ./build/lexer $CFLAGS main.c lexer.c

