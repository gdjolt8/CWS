#include "include/hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HashMap* init_hashmap() {
    HashMap* h = calloc(1, sizeof(HashMap));
    h->entries = init_list();
    return h;
}
void hashmap_clear(HashMap* h) {
    if (h == NULL) return;
    free(h->entries);
    h->entries = init_list();
}

HashMap* hashmap_clone(HashMap* h) {
    HashMap* new_map = init_hashmap();
    for(int i = 0; i < h->entries->used; i++) {
        HashMapEntry* e = (HashMapEntry*)h->entries->items[i];
        hashmap_set(new_map, e->key, e->value);
    }
    return new_map;
}

bool hashmap_contains_key(HashMap* h, char* attemptedKey) {
    for (int i = 0; i < h->entries->used; i++) {
        HashMapEntry* e = (HashMapEntry*)h->entries->items[i];
        if (strcmp(e->key, attemptedKey) == 0) {
            return true;
        }
    }
    return false;
}
bool hashmap_contains_value(HashMap* h, char* attemptedValue) {
    for (int i = 0; i < h->entries->used; i++) {
        HashMapEntry* e = (HashMapEntry*)h->entries->items[i];
        if (strcmp(e->value, attemptedValue) == 0) {
            return true;
        }
    }
    return false;
}
void hashmap_for_each(HashMap* h, void (*func)(char*, char*)) {
    for(int i = 0; i < h->entries->used; i++) {
        HashMapEntry* e = (HashMapEntry*)h->entries->items[i];
        func(e->key, e->value);
    }
}
char* hashmap_get(HashMap* h, char* attemptedKey) {
    for (int i = 0; i < h->entries->used; i++) {
        HashMapEntry* e = (HashMapEntry*)h->entries->items[i];
        if (strcmp(e->key, attemptedKey) == 0) {
            return e->value;
        }
    }
    return NULL;
}
char* hashmap_get_or_default(HashMap* h, char* attemptedKey, char* defValue) {
    for (int i = 0; i < h->entries->used; i++) {
        HashMapEntry* e = (HashMapEntry*)h->entries->items[i];
        if (strcmp(e->key, attemptedKey) == 0) {
            return e->value;
        }
    }
    return defValue;
}
bool hashmap_is_empty(HashMap* h) {
    return h->entries->used == 0;
}
void hashmap_set(HashMap* h, char* attemptedKey, char* attemptedValue) {
    if (h == NULL) return;
    HashMapEntry* e = calloc(1, sizeof(HashMapEntry));
    e->key = attemptedKey;
    e->value = attemptedValue;

    add_element_list(h->entries, e);
}
void hashmap_remove(HashMap* h, char* attemptedKey) {
    HashMap* buf = init_hashmap();
    for(int i = 0; i < h->entries->used; i++) {
        HashMapEntry* e = (HashMapEntry*)h->entries->items[i];
        if(e->key != attemptedKey) hashmap_set(buf, e->key, e->value);
    }
    h = buf;
}
size_t hashmap_size(HashMap* h) {
    return h->entries->used;
}

char* hashmap_to_string(HashMap* h) {
    char* c = calloc(h->entries->used * 64, sizeof(char));
    for(int i = 0; i < h->entries->used; i++) {
        HashMapEntry* e = h->entries->items[i];
        if(e->key == NULL || e->value == NULL) continue;
        char* entry = calloc(strlen(e->key) + strlen(e->value) + 5, sizeof(char));
        sprintf(entry, "%s: %s\n", e->key, e->value);
        strcat(c, entry);
    }
    return c;
}

char* hashmap_get_number_key(HashMap* h, int num) {
    HashMapEntry* entry = h->entries->items[num];
    return entry->key;
}