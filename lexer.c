#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexeme.h"

#define SPECIAL_CHARS "*&#!();_-.?\\:\"'"
#define WHITE_SPACE " \n\t"

Lexemes* lex_file(FILE* file, const char* file_name)
{
    // Find EOF
    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);

    // Go back to file start
    fseek(file, 0L, SEEK_SET);

    // Allcate buffer for file contents
    char *line_contents = malloc(file_size);
    if (line_contents == NULL){
        printf("ERROR: Could not allocate memory for string.\n");
        return NULL;
    }

    // Getting file contents
    int line_number = 0;
    Lexemes *arr = new_darray();

    if(arr == NULL) return NULL;
    while (fgets(line_contents, file_size, file))
    {
        line_number++;
        int col_number = 0;

        char* buffer = malloc(strlen(line_contents));
        if (buffer == NULL) {
            printf("ERROR: Could not allocate memory for buffer! \n");
            return NULL;
        }
        strcpy(buffer, "\0");


        for (int i = 0; i < strlen(line_contents); i++) {
            col_number++;
            const char ch = line_contents[i];

            if (strchr(SPECIAL_CHARS, ch) != NULL || strchr(WHITE_SPACE, ch) != NULL) {
                if (strlen(buffer) > 0) {
                    Position *pos = new_pos(file_name, line_number, col_number);
                    Lexeme *l = new_lexeme(buffer, *pos);
                    // print_lexeme(*l);
                    da_append(arr, *l);
                }

                strncpy(buffer, &ch, 1);
                strncpy(buffer+1, "\0", 1);
                Position *pos = new_pos(file_name, line_number, col_number);
                Lexeme *l = new_lexeme(buffer, *pos);
                // print_lexeme(*l);
                da_append(arr, *l);
                strncpy(buffer, "\0", 1); // Maybe a good idea?
                continue;
            }

            if (isalnum(ch)){
                strncat(buffer, &ch, 1);
                strncpy(buffer+strlen(buffer), "\0", 1);
                col_number--;
                continue;
            }
        }

        free(buffer);
    }
    free(line_contents);

    return arr;
}


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
    if (lexemes == NULL) exit(1);

    fclose(fptr);

    printf("Finished lexing file.\n");

    for(int i = 0; i < lexemes->count; i++) {
        print_lexeme(lexemes->items[i]);
    }

    free_lexemes(lexemes);

    return 0;
}
