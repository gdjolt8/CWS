#include "./include/cws_token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

CWS_TokenLiteral_T tokens[] = {
    {ILLEGAL, "ILLEGAL"},
    {EOF, "EOF"},
    {IDENT, "IDENT"},
    {INT_LITERAL, "INTEGER"},
    {FLOAT_LITERAL, "FLOAT"},
    {STRING_LITERAL, "STRING"},
    {CHAR_LITERAL, "CHAR"},

    {PLUS, "+"},
    {MINUS, "-"},
    {STAR, "*"},
    {SLASH, "/"},
    {LPAREN, "("},
    {RPAREN,")"},
    {LSQB, "["},
    {RSQB, "]"},
    {LBRACE, "{"},
    {RBRACE, "}"},
    {AMPERSAND, "&"},
    {NOT, "!"},
    {OR, "|"},
    {COMMA, ","},
    {DOT, "."},
    {COLON, ":"},
    {ANDAND, "&&"},
    {OROR, "||"},

    {PLUSEQ, "+="},
    {MINUSEQ, "-="},
    {STAREQ, "*="},
    {SLASHEQ, "/="},

    {EQEQ, "=="},
    {NOTEQ, "!="},
    {EQ, "="},
    {SEMI, ";"},
    {GREATER, ">"},
    {GREATEREQ, ">="},
    {LESS, "<"},
    {LESSEQ, "<"},

    {KW_BREAK, "break"},
    {KW_CONST, "const"},
    {KW_CONTINUE, "continue"},
    {KW_ELSE, "else"},
    {KW_FOR, "for"},
    {KW_FUNC, "func"},
    {KW_IF, "if"},
    {KW_MAP, "map"},
    {KW_RETURN, "return"},
    {KW_TYPE, "type"},
    {KW_WHILE, "while"}
};


CWS_TokenLiteral_T keywords[] = {
    {KW_BREAK, "break"},
    {KW_CONST, "const"},
    {KW_CONTINUE, "continue"},
    {KW_ELSE, "else"},
    {KW_FOR, "for"},
    {KW_FUNC, "func"},
    {KW_IF, "if"},
    {KW_MAP, "map"},
    {KW_RETURN, "return"},
    {KW_TYPE, "type"},
    {KW_WHILE, "while"}
};


CWSToken_T *init_token(char* token_value, int token_type)
{
    CWSToken_T* token = calloc(1, sizeof(CWSToken_T));
    token->token_value = token_value;
    token->token_type = token_type;
    return token;
}
char* cws_token_to_string(CWSToken_T* t) {
    char* s = "";
    if (0 <= t->token_type && t->token_type < sizeof(tokens) / sizeof(CWS_TokenLiteral_T)) {
        for (size_t i = 0; i < sizeof(tokens)/sizeof(CWS_TokenLiteral_T); i++)
        {
            if(tokens[i].type == t->token_type) {
                s = calloc(strlen(tokens[i].value) + 1, sizeof(char));
                strcpy(s, tokens[i].value);
            }
        }
    }
    if(s == "") {
        char* s = calloc(strlen(tokens[t->token_type].value) + 1, sizeof(char));
        sprintf(s, "token(%d)", (t->token_type));
    }
    return s;
}
int precedence(CWSToken_T* t) {
    switch (t->token_type)
    {
    case OR:
        return 1;
    case ANDAND:
        return 2;
    case EQEQ:
    case NOTEQ:
    case LESS:
    case LESSEQ:
    case GREATER:
    case GREATEREQ:
        return 3;
    case PLUS:
    case MINUS:
    case OROR:
        return 4;
    case STAR:
    case SLASH:
    case AMPERSAND:
        return 5;
    default:
        return 0;
    }
}

int cws_token_ident_lookup(char* t) {
    for (size_t i = 0; i < sizeof(keywords)/sizeof(CWS_TokenLiteral_T); i++)
    {   
        if (strcmp(keywords[i].value, t) == 0) { 
            return keywords[i].type;
        }
    }
    return IDENT;
    
}
bool cws_token_IsLiteral(CWSToken_T* t) {
    return literal_beg < t->token_type && t->token_type < literal_end;
}
bool cws_token_IsOperator(CWSToken_T* t) {
    return (operator_beg < t->token_type && t->token_type < operator_end);
}
bool cws_token_IsKeyword(CWSToken_T* t) {
    return keyword_beg < t->token_type && t->token_type < keyword_end;
}
bool cws_token_IsIdentifier(CWSToken_T* t) {
    if (strcmp(t->token_value, "") == 0 || cws_token_IsKeyword(t)) {
        return false;
    }
    for(int i = 0; i < strlen(t->token_value); i++) {
        if (!isalpha(t->token_value[i]) && t->token_value[i] != '_' && (i == 0 || isdigit(t->token_value[i]))) {
            return false;
        }
    }
    return true;
}

char* cws_token_position_to_string(CWSTokenPosition_T* p) {
    char* s = calloc(strlen(s) + 33, sizeof(char));
    if (p->line > 0) {
            sprintf(s, "%s:%d:%d", p->filename, p->line, (p->column + 1));
    }
    if (strcmp(p->filename, "") == 0) {
        s = realloc(s, sizeof(char) * 2);
        strcpy(s, "-");
    }
    return s;
}