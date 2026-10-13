#include "utils_questions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

extern char *strdup(const char *);

void print(char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        putchar(str[len++]);
    }
}
void println(char *str)
{
    print(str);
    putchar('\n');
}

bool not_empty(char *str)
{
    return strlen(str) > 0;
}

bool is_number(char *str)
{
    int in_length = strlen(str);

    int start = (char)str[0] == '-' ? 1 : 0;

    if (start == 1 && in_length == 1)
    {
        return false;
    }

    for (int i = start; i < in_length; i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

bool is_float(char *str)
{
    bool has_comma = false;
    int index = 0;
    while (isdigit(str[index]) || str[index] == '.')
    {
        if (str[index++] == '.')
        {
            if (has_comma)
            {
                return false;
            }
            has_comma = true;
        }
    }
    return has_comma;
}

answer_t make_float(char *str)
{
    return (answer_t){.float_value = atof(str)};
}

void clear_input_buffer()
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int read_string(char *buf, int buf_siz)
{
    int c = 0;
    int ch;

    while (c < buf_siz - 1 && (ch = getchar()) != '\n' && ch != EOF)
    {
        buf[c++] = ch;
    }

    buf[c] = '\0';

    if (ch != '\n' && ch != EOF)
        clear_input_buffer();

    return c;
}

answer_t ask_question(char *question, check_func *check, convert_func *convert)
{
    int BUF_SIZE = 255;
    char answer[BUF_SIZE];
    do
    {
        println(question);
        read_string(answer, BUF_SIZE);
    } while (!check(answer));
    return convert(answer);
}

int ask_question_int(char *question)
{
    answer_t answer = ask_question(question, is_number, (convert_func *)atoi);
    return answer.int_value;
}

char *ask_question_string(char *question)
{
    return ask_question(question, not_empty, (convert_func *)strdup).string_value;
}

float ask_question_float(char *question)
{
    return ask_question(question, is_float, make_float).float_value;
}
