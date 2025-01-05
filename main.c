#include <stdio.h>
#include <stdlib.h>
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
    List ptrs = {0};
    ptrs.size = 0;

    Lexemes lexemes = {0};
    lex_file(&ptrs, &lexemes, fptr, file_name);
    fclose(fptr);


    printf("Finished lexing file.\n");

//    for(int i = 0; i < lexemes.count; i++) {
//        print_lexeme(lexemes.items[i]);
//    }

    free_lexemes(&ptrs, &lexemes);
    printf("Unfreed Items: %lu\n", ptrs.size);
    lfree_all(&ptrs);
    printf("Unfreed Items: %lu\n", ptrs.size);


    return 0;
}
