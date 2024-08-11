#!/bin/bash

set -xe
clang -o lexer -O3 main.c lexer.c
