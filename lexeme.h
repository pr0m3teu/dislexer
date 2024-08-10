#ifndef LEXEME_H
#define LEXEME_H


typedef struct {
    char* file_name;
    int line;
    int col;
} Position;


typedef struct {
    Position pos;
    char* value;
} Lexeme;

typedef struct {
    int size;
    int count;
    Lexeme* items;

} Dynamic_Array;


Position* new_pos(const char* const file_name, int line, int col);
void free_pos(Position* pos);

Lexeme* new_lexeme(char* val, Position pos);
void print_lexeme(Lexeme lexeme);
void free_lexeme(Lexeme* lexeme);

Dynamic_Array* new_darray();
int da_append(Dynamic_Array* arr, Lexeme item);
void free_darray(Dynamic_Array* arr);
#endif // LEXEME_H
