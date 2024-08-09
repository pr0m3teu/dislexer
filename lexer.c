
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexeme.h"

int main(int argv, char* argc[])
{
    FILE *fptr = NULL;
    char file_name[] = "test.txt";
    fptr = fopen(file_name, "r");

    if (fptr == NULL)
    {
        printf("ERROR: Could not open file %s\n", file_name);
        exit(1);
    }

    // Find EOF
    fseek(fptr, 0L, SEEK_END);
    long file_size = ftell(fptr);
    printf("file %s is %ld bytes long.\n", file_name, file_size);
    // Go back to file start
    fseek(fptr, 0L, SEEK_SET);

    // Allcate buffer for file contents
    char *line_contents = malloc(file_size);
    if (line_contents == NULL){
        printf("ERROR: Could not allocate memory for string.\n");
        exit(1);
    }

    // Getting file contents
    const char special_chars[] = "#!()";
    const char white_space[] = " \n\t";

    int line_number = 0;
    while (fgets(line_contents, file_size, fptr))
    {
        line_number++;
        int col_number = 0;

        char* buffer = malloc(strlen(line_contents));
        if (buffer == NULL) {
            printf("ERROR: Could not allocate memory for buffer! \n");
            exit(1);
        }
        strcpy(buffer, "\0");


        for (int i = 0; i < strlen(line_contents); i++) {
            col_number++;
            const char ch = line_contents[i];
            // printf("/%s:%d:%d : %c\n", file_name, line_number, col_number, ch);

            if (strchr(special_chars, ch) != NULL || strchr(white_space, ch) != NULL) {
                if (strlen(buffer) > 0) {
                    // printf("curr buffer: %s\n", buffer);
                    Position *pos = new_pos(file_name, line_number, col_number);
                    Lexeme *l = new_lexeme(buffer, *pos);
                    print_lexeme(*l);
                    free_lexeme(l);
                }

                strncpy(buffer, &ch, 1);
                strncpy(buffer+1, "\0", 1);
                Position *pos = new_pos(file_name, line_number, col_number);
                Lexeme *l = new_lexeme(buffer, *pos);
                print_lexeme(*l);
                free_lexeme(l);
                strncpy(buffer, "\0", 1); // Maybe a good idea?
                continue;
            }

            if (isalnum(ch)){
                strncat(buffer, &ch, 1);
                strncpy(buffer+strlen(buffer), "\0", 1);
                col_number--;
            }
        }

        free(buffer);
    }
    free(line_contents);
    fclose(fptr);

    return 0;
}
