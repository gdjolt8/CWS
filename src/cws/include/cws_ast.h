#ifndef CWS_AST_H
#define CWS_AST_H

#include "../utils/include/list.h"
#include "cws_data_type.h"
#include <stdbool.h>

enum AST_Type
{
    AST_BLOCK,
    AST_FUNCTION_CALL,
    AST_FUNCTION_DEFINITION,
    AST_ASSIGNMENT,
    AST_TYPE_DEFINITION,
    AST_VARIABLE,
    AST_VARIABLE_DEFINITION,
    AST_RETURN_STATEMENT,
    AST_IF_STATEMENT,
    AST_WHILE_STATEMENT,
    AST_FOR_STATEMENT,
    AST_OBJECT_ATTRIBUTE,
    AST_ARRAY,
    AST_TYPE,
    AST_INTEGER,
    AST_FLOAT,
    AST_BOOLEAN,
    AST_CHAR,
    AST_STRING,
    AST_BINOP,
    AST_UNOP,
    AST_VOID
};

typedef struct CWS_AST_STRUCT
{
    int ast_type;
    list_T* block_statements;
    struct CWS_AST_STRUCT* function_call_name;
    list_T* function_call_arguments;
    struct CWS_AST_STRUCT* function_definition_name;
    CWSDataType_T* function_definition_type;
    list_T* function_definition_params;
    struct CWS_AST_STRUCT* function_definition_block;
    struct CWS_AST_STRUCT* assignment_left_op;
    struct CWS_AST_STRUCT* assignment_right_op;
    struct CWS_AST_STRUCT* type_definition_name;
    struct CWS_AST_STRUCT* type_definition_block;
    struct CWS_AST_STRUCT* variable_name;

    struct CWS_AST_STRUCT* variable_definition_name;
    CWSDataType_T* variable_definition_type;
    struct CWS_AST_STRUCT* variable_definition_value;

    struct CWS_AST_STRUCT* return_value;

    struct CWS_AST_STRUCT* if_statement_condition;
    struct CWS_AST_STRUCT* if_statement_body;

    struct CWS_AST_STRUCT* while_statement_condition;
    struct CWS_AST_STRUCT* while_statement_body;

    struct CWS_AST_STRUCT* for_statement_definition; // i: int = 0
    struct CWS_AST_STRUCT* for_statement_condition; // i < 5
    struct CWS_AST_STRUCT* for_statement_loop; // i += 1
    struct CWS_AST_STRUCT* for_statement_body; // { i ... }

    list_T* array_object_children;

    long long int_literal_value;
    long double float_literal_value;
    bool boolean_literal_value;
    char char_literal_value;
    char* string_literal_value;

    struct CWS_AST_STRUCT* binop_left;
    int binop_op;
    struct CWS_AST_STRUCT* binop_right;

    int unop_op;
    struct CWS_AST_STRUCT* unop_right;
} AST_T;

#endif