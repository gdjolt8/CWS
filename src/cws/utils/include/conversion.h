#ifndef CONVERSION_H
#define CONVERSION_H
#include <stdbool.h>
#include "hashmap.h"

char* convert_int_to_string(int num);
char* cutoff_by(char* s, char* c);
bool is_char_in_string(char* s, char c);
HashMap* convert_params_to_map(char* params);
char* str_format(char* instr);
char str_to_escape_seq(const char* instr);
#endif