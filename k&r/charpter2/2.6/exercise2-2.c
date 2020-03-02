#include <stdio.h>

/* 再不试用运算符&&或||的条件下编写一个与上面的for循环语句等价的循环语句。 */
int main()
{
    int i, c ,j;
    //int lim = 1000;
    i = 0;
    char s[1000];
    // for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
    //     s[i] = c;
    do
    {
        c = getchar();
        if (c == '\n' || c == EOF )
            break;
        s[i] = c;
        ++i;
    } while (1);

    for (j =0; j < i; ++j)
        putchar(s[j]);
}

