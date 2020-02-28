#include <stdio.h>

/* count lines in intput; 1st version*/
int main()
{
    int c, nl;
    nl = 0;
    while((c = getchar()) != EOF)
        if ( c == '\n')
            ++nl;
    printf("%d\n", nl);
}