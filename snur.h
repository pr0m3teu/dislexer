#ifndef SNUR_H_ 
#define SNUR_H_

#ifndef DEFAULT_SIZE
#define DEFAULT_SIZE 128
#endif

typedef struct {
    char *items;
    size_t len;
    size_t size;
} Snur;

typedef struct {
    char *items;
    size_t len;
} Snur_View;

#define sn_append_null(snur) sn_append_char(snur, "\0")


void sn_init(Snur* snur);
void sn_free(Snur* snur);
void sn_from_cstr(Snur* snur, const char* cstr);
void sn_append_char(Snur* snur, const char* ch);
void sn_append_many(Snur* snur, const char* str, size_t len);
void sn_append_cstr(Snur* snur, const char* cstr);
void sn_clear(Snur* snur);
char sn_pop_char(Snur* snur);


Snur_View sn_build_snur(Snur snur);



#endif // SNUR_H_
