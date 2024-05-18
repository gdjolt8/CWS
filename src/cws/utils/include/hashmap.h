#ifndef HASHMAP_H
#define HASHMAP_H

#include "list.h"
#include <stdbool.h>
#include <inttypes.h>
typedef struct HASHMAP_ENTRY_STRUCT {
    char* key;
    char* value;
} HashMapEntry;

typedef struct HASHMAP_STRUCT {
    list_T* entries;
} HashMap;

HashMap* init_hashmap();
void hashmap_clear(HashMap* h);
HashMap* hashmap_clone(HashMap* h);
bool hashmap_contains_key(HashMap* h, char* attemptedKey);
bool hashmap_contains_value(HashMap* h, char* attemptedValue);
void hashmap_for_each(HashMap* h, void (*func)(char*, char*));
char* hashmap_get(HashMap* h, char* attemptedKey);
char* hashmap_get_or_default(HashMap* h, char* attemptedKey, char* defValue);
bool hashmap_is_empty(HashMap* h);
void hashmap_set(HashMap* h, char* attemptedKey, char* attemptedValue);
void hashmap_remove(HashMap* h, char* attemptedKey);
size_t hashmap_size(HashMap* h);
char* hashmap_to_string(HashMap* h);
char* hashmap_get_number_key(HashMap* h, int num);
#endif