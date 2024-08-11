#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

int main(int argv, char* argc[])
{
    if (argv < 2) {
        printf("ERROR: No file is provided!\n");
        printf("Usage: lexer <file>\n");
        exit(1);
    }
    FILE *fptr = NULL;

    char* file_name = argc[1];
    fptr = fopen(file_name, "rb");

    if (fptr == NULL) {
        printf("ERROR: Could not open file %s\n", file_name);
        exit(1);
    }

    Lexemes *lexemes = lex_file(fptr, file_name);
    fclose(fptr);
    if (lexemes == NULL) exit(1);


    printf("Finished lexing file.\n");

    for(int i = 0; i < lexemes->count; i++) {
        print_lexeme(lexemes->items[i]);
    }

    free_lexemes(lexemes);

    return 0;
}