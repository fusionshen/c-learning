#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000 /* maximum input line length */

int getline(char line[], int maxline);
void reverse(char s[]);

/* 编写一个递归版本的 reverse(s)函数,以将字符串s倒置。 */
int main()
{
    char s[MAXLINE];
    getline(s, MAXLINE);
    reverse(s);
    printf("%s\n", s);
    return 0;
}

/* getline: read a line into s return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    // if (c == '\n') {
    //     s[i] = c;
    //     ++i;
    // }
    s[i] = '\0';
    return i;
}


void reverse(char s[])
{
    int c, j;
    static int i = 0;
    j = strlen(s) - 1;
    c = s[i];
    s[i] = s[j - i];
    s[j - i] = c;
    i++;
    if (i < j/2 + 1) {
        reverse(s);
    }
}
