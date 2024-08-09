#!/bin/bash

set -xe
clang -o lexer -O3 lexer.c lexeme.c
