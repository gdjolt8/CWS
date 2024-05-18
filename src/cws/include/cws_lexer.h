#ifndef CWS_LEXER_H
#define CWS_LEXER_H

#include <stdio.h>
#include "cws_token.h"

typedef struct CWS_LEXER_STRUCT {
    char* source;

    char current_char;
    int offset;
    int colOffset;
    int lineOffset;

    int errorCount;
} CWSLexer_T;

CWSLexer_T* init_cws_lexer(char* source);
void cws_lexer_read_next_char(CWSLexer_T* l);
char cws_lexer_peek(CWSLexer_T* l, int offset);
void cws_lexer_scan_whitespace(CWSLexer_T* l);
void cws_lexer_scan_comment(CWSLexer_T* l);
CWSToken_T* cws_lexer_scan_next_token(CWSLexer_T* l);
CWSToken_T* cws_lexer_scan_next_identifier(CWSLexer_T* l);
CWSToken_T* cws_lexer_scan_next_integer(CWSLexer_T* l);
CWSToken_T* cws_lexer_scan_next_string(CWSLexer_T* l);
CWSToken_T* cws_lexer_scan_next_character(CWSLexer_T* l);
CWSToken_T* cws_lexer_read_number_token(CWSLexer_T* l);

#endif