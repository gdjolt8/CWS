#include "./include/conversion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a,b) (a > b ? b : a)
char* convert_int_to_string(int num) {
    char* buffer = calloc(16, sizeof(char));
    sprintf(buffer, "%d", num);
    return buffer;
}

char* cutoff_by(char* s, char* c) {
    char* new_string = calloc(strlen(s), sizeof(char));
    for(int i = 0; i < strlen(s); i++) {
        if (is_char_in_string(c, s[i])) break;
        new_string[i] = s[i];
    }
    return new_string;
}

bool is_char_in_string(char* s, char c) {
    for(int i = 0; i < strlen(s); i++) {
        if (s[i] == c) return true;
    }
    return false;
}

HashMap* convert_params_to_map(char* params) {
    char* c = strchr(params, params[1]);
    list_T* params_list = split(c, "&");
    HashMap* h = init_hashmap();
    for (size_t i = 0; i < params_list->used; i++)
    {
        list_T* kvs = split((char*)params_list->items[i], "=");
        hashmap_set(h, kvs->items[0], kvs->items[1]);
    }
    return h;
    
}

char* str_format(char* instr) {
  char* newstr = calloc(1, sizeof(char));
  unsigned int len = strlen(instr);

  unsigned int i = 0;
  while (instr[i] != '\0' && i < len)
  {
    newstr = realloc(newstr, (strlen(newstr) + 2) * sizeof(char));

    if (instr[i] == '\\')
    {
      char escape = str_to_escape_seq((char[]){ instr[i], instr[MIN(i+1, len)], 0 });
      strcat(newstr, (char[]){escape, 0});
      i += 2;
    }
    else
    {
      strcat(newstr, (char[]){instr[i], 0});
      i += 1;
    }
  }

  return newstr;
}

char str_to_escape_seq(const char* instr)
{
  if (strlen(instr) <= 1) return 0;
  if (instr[0] != '\\') return 0;
  char in_c = instr[1];

  switch (in_c)
  {
    case 'n': return '\n';
    case 't': return '\t';
    case 'r': return '\r';
    case '\\': return in_c;
    default: return in_c;
  }

  return in_c;
}