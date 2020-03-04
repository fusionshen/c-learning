#include <stdio.h>
#include <ctype.h>

int lower(int c);

/*
** 重新编写将大写字母转换为小写字母的函数lower，并用条件表达式替代其中的if-else结构。
*/

int main()
{
    int c, i, j;
    char s[1000];
    printf("enter your string(end it with Enter key): ");
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    printf("the lower string is:");
    j = 0;
    while(j < i)
    {
        putchar(lower(s[j++]));
    }

}

/* lower: covert c to lower case; ASCII only */
int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
