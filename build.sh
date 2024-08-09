#!/bin/bash

set -xe
clang -o lexer lexer.c lexeme.c
