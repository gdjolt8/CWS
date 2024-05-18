#ifndef CWS_TOKEN_H
#define CWS_TOKEN_H
#include <stdio.h>
#include <stdbool.h>

enum TokenType 
{
    ILLEGAL = 0,

    // Literals

    literal_beg,
    IDENT,
    INT_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,
    CHAR_LITERAL,
    literal_end,
    // Grammar
    operator_beg,
    LPAREN, RPAREN,  LSQB, RSQB, COMMA, SEMI, PLUS, MINUS, STAR, SLASH,
    PLUSEQ, MINUSEQ, STAREQ, SLASHEQ,
    AMPERSAND, OR, NOT, LESS, GREATER, LESSEQ, GREATEREQ, EQ, DOT,
    ANDAND, OROR, COLON,
    LBRACE, RBRACE, EQEQ, NOTEQ, GREATEREQUAL,
    operator_end,

    keyword_beg,
    KW_BREAK,
    KW_CONST,
    KW_CONTINUE,

    KW_ELSE,
    KW_FOR,
    KW_FUNC,
    KW_IF,

    KW_MAP,
    KW_RETURN,
    KW_TYPE,
    KW_WHILE,
    keyword_end
};

typedef struct CWS_POSITION_STRUCT {
    char* filename;
    int offset;
    int line;
    int column;
} CWSTokenPosition_T;

typedef struct CWS_TOKEN_LITERAL_STRUCT {
    int type;
    char* value;
} CWS_TokenLiteral_T;
typedef struct CWS_TOKEN_STRUCT {
    char* token_value;
    enum TokenType token_type; 
    CWS_TokenLiteral_T* position;
} CWSToken_T;


char* cws_token_to_string(CWSToken_T* t);
int precedence(CWSToken_T* t);

int cws_token_ident_lookup(char* t);
bool cws_token_IsLiteral(CWSToken_T* t);
bool cws_token_IsOperator(CWSToken_T* t);
bool cws_token_IsKeyword(CWSToken_T* t);
bool cws_token_IsIdentifier(CWSToken_T* t);

char* cws_token_position_to_string(CWSTokenPosition_T* p);

CWSToken_T *init_token(char* token_value, int token_type);
#endif