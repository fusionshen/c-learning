#include <stdio.h>
#include <limits.h>
#include <string.h>

void reverse(char s[]);
void itoa(int n, char s[], int w);

/*
** 修改itoa函数，使得该函数可以接受三个参数。其中，第三个参数为最小字段宽度。为了保证转换后所得的结果
** 至少具有第三个参数指定的最小宽度，在必要时应在所得结果的左边填充一定的空格。
*/
int main()
{
    int n = INT_MIN;
    char s[100];
    itoa(n, s, 14);
    printf("%s\n", s);
    return 0;
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


void itoa(int n, char s[], int w)
{
    int i = 0;
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
        s[i++] = n_copy % 10 + '0';
    } while ((n_copy /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    while(i < w) {
        s[i++] = ' ';
    }
    s[i++] = '\0';
    reverse(s);
}
