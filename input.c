#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_BUFFER_SIZE 10

char *read_line()
{
    int size = DEFAULT_BUFFER_SIZE;
    char *str;
    str = (char *)calloc(size, sizeof(char));
    char c;
    c = getchar();
    int i = 0;
    while (c != '\n')
    {
        if (i >= size)
        {
            size = size * 2;
            str = (char *)realloc(str, size);
        }
        str[i] = c;
        c = getchar();
        ++i;
    }
    str[i] = '\0';
    return str;
}
