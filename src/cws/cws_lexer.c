#include "./include/cws_lexer.h"
#include "./utils/include/conversion.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

CWSLexer_T* init_cws_lexer(char* source) {
    CWSLexer_T* lexer = calloc(1, sizeof(CWSLexer_T));
    lexer->source = source;
    lexer->offset = 0;
    lexer->current_char = source[lexer->offset];
    lexer->lineOffset = 0;
    lexer->colOffset = 0;
    lexer->errorCount = 0;

    return lexer;
}
void cws_lexer_read_next_char(CWSLexer_T* l) {
    l->offset++;
    l->colOffset++;
    if (l->offset >= strlen(l->source)) {
        l->current_char = 0;
        return;
    }
    l->current_char = l->source[l->offset];
    if(l->current_char == '\n') {
        l->lineOffset++;
        l->colOffset = 0;
    }
}
char cws_lexer_peek(CWSLexer_T* l, int offset) {
    if (l->offset + offset >= strlen(l->source))
        return '\0';
    return l->source[l->offset+offset];
}
void cws_lexer_scan_whitespace(CWSLexer_T* l) {
    while (l->current_char == ' ' || l->current_char == '\t' || l->current_char == '\r' || l->current_char == '\n')
    {
        cws_lexer_read_next_char(l);
    }
    
}
void cws_lexer_scan_comment(CWSLexer_T* l) {
    if (l->current_char == '/' && cws_lexer_peek(l, 1) == '/') {
        while (!l->current_char == '\n')
        {
            cws_lexer_read_next_char(l);
        }
    } else if (l->current_char == '/' && cws_lexer_peek(l, 1) == '*')
    {
        while (1) {
            if (l->current_char == '*' && cws_lexer_peek(l, 1) == '/') {
                cws_lexer_read_next_char(l);
                cws_lexer_read_next_char(l);
                break;
            }
            cws_lexer_read_next_char(l);
        }
    }
    cws_lexer_scan_whitespace(l);
    
}

CWSToken_T* init_token_advance(CWSLexer_T* l, CWSToken_T* t) {
    for(int i = 0; i < strlen(t->token_value); i++) cws_lexer_read_next_char(l);
    return t;
}

CWSToken_T* cws_lexer_scan_next_token(CWSLexer_T* l) {
    cws_lexer_scan_whitespace(l);
    cws_lexer_scan_comment(l);

    if (isalpha(l->current_char))
    {
        return cws_lexer_scan_next_identifier(l);
    }
    if (isdigit(l->current_char)) {
        return cws_lexer_read_number_token(l);
    }

    if (l->current_char == '\"') {
        return cws_lexer_scan_next_string(l);
    }

    if (l->current_char == '\'') {
        return cws_lexer_scan_next_character(l);
    }
    
    CWSToken_T *token = NULL;

    switch (l->current_char)
    {
        case '+': {
            if (cws_lexer_peek(l, 1) == '='){
                return init_token_advance(l, init_token("+=", PLUSEQ));
            }
            return init_token_advance(l, init_token("+", PLUS));
        }
        case '-': {
            if (cws_lexer_peek(l, 1) == '='){
                return init_token_advance(l, init_token("-=", MINUSEQ));
            }
            return init_token_advance(l, init_token("-", MINUS));
        }
        case '*': {
            if (cws_lexer_peek(l, 1) == '='){
                return init_token_advance(l, init_token("*=", STAREQ));
            }
            return init_token_advance(l, init_token("*", STAR));
        }
        case '/': {
            if (cws_lexer_peek(l, 1) == '='){
                return init_token_advance(l, init_token("/=", SLASHEQ));
            }
            return init_token_advance(l, init_token("/", SLASH));
        }

        case '&': {
            if (cws_lexer_peek(l, 1) == '&'){
                return init_token_advance(l, init_token("&&", ANDAND));
            }
            return init_token_advance(l, init_token("&", AMPERSAND));
        }
        case '|': {
            if (cws_lexer_peek(l, 1) == '|'){
                return init_token_advance(l, init_token("||", OROR));
            }
            return init_token_advance(l, init_token("|", OR));
        }
        case '=': {
            if (cws_lexer_peek(l, 1) == '='){
                return init_token_advance(l, init_token("==", EQEQ));
            }
            return init_token_advance(l, init_token("=", EQ));
        }
        case '!': {
            if (cws_lexer_peek(l, 1) == '='){
                return init_token_advance(l, init_token("!=", NOTEQ));
            }
            return init_token_advance(l, init_token("!", NOT));
        }
        case '>': {
            if (cws_lexer_peek(l, 1) == '='){
                return init_token_advance(l, init_token(">=", GREATEREQ));
            }
            return init_token_advance(l, init_token(">", GREATER));
        }
        case '<': {
            if (cws_lexer_peek(l, 1) == '='){
                return init_token_advance(l, init_token("<=", LESSEQ));
            }
            return init_token_advance(l, init_token("<", LESS));
        }
        case '(': return init_token_advance(l, init_token("(", LPAREN));
        case ')': return init_token_advance(l, init_token(")", RPAREN));
        case '{': return init_token_advance(l, init_token("{", LBRACE));
        case '}': return init_token_advance(l, init_token("}", RBRACE));
        case '[': return init_token_advance(l, init_token("[", LSQB));
        case ']': return init_token_advance(l, init_token("]", RSQB));
        case ',': return init_token_advance(l, init_token(",", COMMA));
        case ';': return init_token_advance(l, init_token(";", SEMI));
        case ':': return init_token_advance(l, init_token(":", COLON));
        case '.': return init_token_advance(l, init_token("{", DOT));
        case 0: return init_token("<EOF>", EOF);
    }

    fprintf(stderr, "Invalid character: (%c): (%d)", l->current_char, (int)l->current_char);
    exit(1);
}
CWSToken_T* cws_lexer_scan_next_identifier(CWSLexer_T* l) {
    char* value = calloc(1, sizeof(char));
    while (isalnum(l->current_char)) {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){l->current_char, 0});
        cws_lexer_read_next_char(l); 
    }
    return init_token(value, cws_token_ident_lookup(value));
}
CWSToken_T* cws_lexer_scan_next_integer(CWSLexer_T* l) {
    char* value = calloc(1, sizeof(char));

    while (isdigit(l->current_char))
    {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){l->current_char, 0});
        cws_lexer_read_next_char(l);
    }

    return init_token(value, INT_LITERAL);
    
}
CWSToken_T* cws_lexer_scan_next_string(CWSLexer_T* l) {
    char* value = calloc(1, sizeof(char));
    cws_lexer_read_next_char(l);

    while (l->current_char != '"') {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){l->current_char, 0});
        cws_lexer_read_next_char(l);
    }

    cws_lexer_read_next_char(l);
    char* fmt = str_format(value);
    free(value);

    return init_token(fmt, STRING_LITERAL);
}
CWSToken_T* cws_lexer_scan_next_character(CWSLexer_T* l) {
    char* value = calloc(1, sizeof(char));
    cws_lexer_read_next_char(l);

    while (l->current_char != '\'') {

        if (strlen(value) > 1)
        {
            fprintf(stderr, "Character too long\n");
            exit(1);
        }
        
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){l->current_char, 0});
        cws_lexer_read_next_char(l);
    }
    cws_lexer_read_next_char(l);
    char* fmt = str_format(value);
    free(value);

    return init_token(fmt, CHAR_LITERAL);
}
CWSToken_T* cws_lexer_read_number_token(CWSLexer_T* l) {
    CWSToken_T* int_l = cws_lexer_scan_next_integer(l);
    if (l->current_char != '.') return int_l;
    // Float literal
    cws_lexer_read_next_char(l);
    if (!isdigit(l->current_char)) {
        fprintf(stderr, "Expected integer value, got %c\n", l->current_char);
        exit(1);
    }   

    CWSToken_T* frac = cws_lexer_scan_next_integer(l);

    char* fmt = calloc(strlen(int_l->token_value) + strlen(frac->token_value) + 2, sizeof(char));
    sprintf(fmt, "%s.%s", int_l->token_value, frac->token_value);
    return init_token(fmt, FLOAT_LITERAL);
}