#include <stdio.h>
#include <string.h>
#define MAX 100

void itob(int n, char s[], int b);
void reverse(char s[]);

/*
** 编写函数itob(n,s,b),将整数n转换为以b为底的数，并将转换结果以字符的形式保存到字符串s中。
** 例如，itob(n,s,16)把整数n格式化成十六进制整数保存在s中。
*/
int main()
{
    int n, b;
    char s[MAX];
    n = -211;
    b = 16;
    itob(n, s, b);
    printf("%s", s);
    return 0;
}

void itob(int n, char s[], int b)
{

    int i = 0, j;
    int sign = n;
    unsigned n_copy;
    if ((sign = n) < 0) {
        if((n-1) > 0)
            n_copy = n;
        else
            n_copy = -n;
    } else
        n_copy = n;
    do {
        j = n_copy % b;
        s[i++] = j < 9 ? j + '0' : j + 'A' - 10;
    } while ((n_copy /= b) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int c, i, j;
    for(i = 0, j = strlen(s) - 1; i < j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

