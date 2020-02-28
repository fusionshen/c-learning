#include <stdio.h>

/* count empty spaces,tables,lines in intput; 1st version*/
int main()
{
    int c, es, ts, nl;
    es = 0;
    ts = 0;
    nl = 0;
    while((c = getchar()) != EOF)
        if ( c == '\n')
            ++nl;
        else if ( c == ' ')
            ++es;
        else if ( c == '\t')
            ++ts;
    printf("lines:%d,empty spaces:%d,tables: %d\n", nl, es, ts);
}