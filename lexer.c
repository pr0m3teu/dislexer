#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

#define DEFAULT_SIZE 256
#define SPECIAL_CHARS "*&#!();_-.?\\:\"'"
#define WHITE_SPACE " \n\t"

Position* new_pos(const char* const file_name, int line, int col)
{
    Position* pos = malloc(sizeof(Position));
    if (pos == NULL) return NULL;

    pos->file_name = malloc(sizeof(strlen(file_name)));
    if (pos->file_name == NULL) return NULL;
    // pos->file_name = file_name; This should be wrong.
    strncpy(pos->file_name, file_name, strlen(file_name)); // This should be correct.
    pos->line = line;
    pos->col = col;

    return pos;
}


void free_pos(Position* pos)
{
    if (pos != NULL)
    {

        free(pos->file_name);
        free(pos);

    }
}

Lexeme* new_lexeme(char* val, Position pos)
{
    Lexeme* lexeme = malloc(sizeof(Lexeme));
    if (lexeme == NULL) return NULL;

    lexeme->value = malloc(strlen(val));
    if (lexeme->value == NULL) return NULL;
    strncpy(lexeme->value, val, strlen(val));
    strncpy(lexeme->value+strlen(val),"\0" , 1);
    lexeme->pos = pos;

    return lexeme;
}

void print_lexeme(Lexeme lexeme)
{
    if (lexeme.value == NULL)
    {
        printf("ERROR: Lexeme seems to be empty!\n");
        return;
    }
    printf("/%s:%d:%d : ", lexeme.pos.file_name, lexeme.pos.line, lexeme.pos.col);
    printf("%s\n", lexeme.value);

}

void free_lexeme(Lexeme *lexeme)
{
    if (lexeme != NULL)
    {

        free_pos(&lexeme->pos);
        free(lexeme->value);
    }
}

Lexemes* new_darray()
{
    Lexemes* arr = malloc(sizeof(Lexemes));
    if (arr == NULL) return NULL;

    arr->size = DEFAULT_SIZE;
    arr->count = 0;
    arr->items = malloc(DEFAULT_SIZE * sizeof(Lexeme));

    if (arr->items == NULL) return NULL;

    return arr;
}

int da_append(Lexemes *arr, Lexeme item)
{
    if (arr->count < arr->size)
    {
        arr->items[arr->count] = item;
    }
    else
    {
        arr->size += DEFAULT_SIZE;
        arr->items = realloc(arr->items, (arr->size)*sizeof(Lexeme));
        if(arr->items == NULL) return -1;
        arr->items[arr->count] = item;
    }
    arr->count++;
    return 0;
}

void free_lexemes(Lexemes *arr)
{
    // TODO: Make this work so it doesn't leak memory.
    // for (int i = 0; i < arr->count; i++) {
    //     free_lexeme(&arr->items[i]);
    // }

    free(arr->items);

    free(arr);
    printf("Freed da_array.\n");
}

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
                    da_append(arr, *l);
                }

                strncpy(buffer, &ch, 1);
                strncpy(buffer+1, "\0", 1);
                Position *pos = new_pos(file_name, line_number, col_number);
                Lexeme *l = new_lexeme(buffer, *pos);
                da_append(arr, *l);
                strncpy(buffer, "\0", 1);
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
