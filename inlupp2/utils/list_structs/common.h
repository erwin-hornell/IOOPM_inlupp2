#pragma once
#include <stdbool.h>

/**
* @file common.h
* @author write both your names here
* @date 01/10/2026
* @brief union value and macros
*
*/


#define INT_AS_ELEM(v)   ((value_t) { .i = (v) })
#define BOOL_AS_ELEM(v)  ((value_t) { .b = (v) })
#define FLOAT_AS_ELEM(v) ((value_t) { .f = (v) })
#define PTR_AS_ELEM(v)   ((value_t) { .p = (v) })

typedef union value value_t;
union value
{
    int i;
    bool b;
    float f;
    void *p;
};