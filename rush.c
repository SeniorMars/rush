#include "rush.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
// basics
// input
// greeting
//
int main(int argc, char *argv[])
{
    char *str = read_line();
    parse_line(str);
    printf("Inputted string: %s", str);
    free(str);
    return 0;
}