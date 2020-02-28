#include <stdio.h>

/* count characters in intput; 1st version*/
int main()
{
    int nc;
    nc = 0;
    while(getchar() != EOF)
        ++nc;
    printf("%1d\n", nc);
}