#include <stdio.h>
#include <ctype.h>
#define YES 1
#define NO 0

int htoi(char s[]);

/* 编写函数htoi(s),把十六进制数字组成的字符串(包含可选的前缀0x或0X)转化为与之等价的
** 整型值。字符串中允许包含的数字包括: 0~9、a~f以及A~F。
*/

int main()
{
    int c, i;
    char s[1000];
    printf("enter your hexadecimal string，you can start it with 0x or 0X optionally: ");
    for (i = 0; (c = getchar()) != EOF && (isdigit(c) || isalpha(c)); ++i)
        s[i] = c;
    printf("the number is:%d ", htoi(s));
}

 /* htoi: covert hexadecimal string s to interger */
int htoi(char s[])
{
    int hexdigit, i, inhex, n;
    i = 0;
    if (s[i] == '0')
    {
        ++i;
        if (s[i] == 'x' || s[i] == 'X')
        {
            ++i;
        }
    }
    n = 0;
    inhex = YES;
    hexdigit = 0;
    for (; inhex == YES; ++i)
    {
        if (s[i] >= '0' && s[i] <= '9')
            hexdigit = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            hexdigit = s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            hexdigit = s[i] - 'A' + 10;
        else
            inhex = NO;
        if (inhex == YES)
            n = 16 * n + hexdigit;
    }

    return n;
}
