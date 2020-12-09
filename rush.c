#include "rush.h"
#include "input.h"
#include <stdio.h>
// basics
// input
// greeting
//
int main(int argc, char *argv[])
{
    char *str = read_line();
    printf("Inputted string: %s", str);
    free(str);
    return 0;
}