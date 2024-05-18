#ifndef CWS_DATA_TYPE_H
#define CWS_DATA_TYPE_H

#include <stdint.h>
#include "../utils/include/list.h"

enum DataType
{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_VOID,
    
    TYPE_ARRAY
};

typedef struct CWS_DATA_TYPE
{
    int data_type;
    int array_data_type;    
} CWSDataType_T;
#endif