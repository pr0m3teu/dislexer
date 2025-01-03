#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "snur.h"

static void check_ptr(void* ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "[ERROR]: Could not allocate memory\n");
        exit(1);
    }
}

void sn_init(Snur* snur)
{
    snur->items = malloc(sizeof(char) * DEFAULT_SIZE);
    check_ptr(snur->items);

    snur->size = DEFAULT_SIZE;
    snur->len = 0;
}

void sn_free(Snur* snur)
{
    free(snur->items);
    snur->items = NULL;
    snur->size = 0;
    snur->len = 0;
}

void sn_from_cstr(Snur* snur, const char* cstr)
{
    size_t len = strlen(cstr);
    if (snur->len > snur->size) 
    {
        if (snur->items == NULL) snur->items = malloc(sizeof(char) * len);
        else snur->items = realloc(snur->items, sizeof(char) * len);
    }
    check_ptr(snur->items);

    snur->len = len;
    snur->size = len;
}

static void sn_resize(Snur* snur)
{
    snur->items = realloc(snur->items, snur->size*2);
    check_ptr(snur->items);
    snur->size = snur->size * 2;
}

void sn_append_char(Snur* snur, const char* ch)
{
    if (snur->len == snur->size)
    { 
        sn_resize(snur);
    }
    snur->items[snur->len] = ch[0];
    snur->len++;
}

void sn_append_many(Snur* snur, const char* str, size_t len)
{
    if (snur->len + len >= snur->size)
    {
        sn_resize(snur);
    }

//    for (size_t i = 0; i < len; ++i)
//    {
//        snur->items[snur->len + i] = str[i];
//    }

    strncpy(snur->items + snur->len, (char*)str, len);
    snur->len += len;
}

void sn_append_cstr(Snur* snur, const char* cstr)
{
    size_t len = 0;
    while (cstr[len] != '\0')
    {
        len++;
    }

    sn_append_many(snur, cstr, len);
}

char sn_pop_char(Snur* snur)
{
    return snur->items[snur->len--];
}

void sn_clear(Snur* snur)
{
    snur->len = 0;
}

Snur_View sn_build_snur(Snur snur)
{
    Snur_View sn = {0};
    sn.items = malloc(sizeof(char )* snur.len);
    //for (size_t i = 0; i < snur.len; i++)
    //{
    //    sn.items[i] = snur.items[i];
    //}
    strncpy(sn.items, snur.items, snur.len);
    sn.items[snur.len] = '\0';
    sn.len = snur.len;
    return sn; 
}
