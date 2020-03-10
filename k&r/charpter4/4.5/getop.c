#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getop: get next character or numberic operand */
/* 增加负数情况 */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* not a number */
    i = 0;
    if (c == '-') /* maybe a number */
        s[++i] = c = getch();
    if (isdigit(c))  /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') /* collect fraction part*/
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    if (s[i-1] == '-')
        return '-'; /* just - */
    return NUMBER;
}
