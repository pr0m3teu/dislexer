#!/bin/bash

set -xe
CFLAGS="-Wall -Wextra -O3"  

clang -o lexer $CFLAGS main.c lexer.c

