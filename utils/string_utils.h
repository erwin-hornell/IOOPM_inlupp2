#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* TODO description
*/
typedef union
{
    int int_value;
    float float_value;
    char *string_value;
} answer_t;
/*
* TODO description
*/
typedef bool check_func(char *);
typedef answer_t convert_func(char *);

/*
* TODO description
*/
int ask_question_int(char *question);
/*
* TODO description
*/
char *ask_question_string(char *question);
/*
* TODO description
*/
float ask_question_float(char *question);
/*
* TODO description
*/
answer_t ask_question(char *question, check_func *check, convert_func *convert);