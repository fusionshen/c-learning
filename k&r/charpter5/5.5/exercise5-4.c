#include <stdio.h>
#include <string.h>
#define MAXLEN 100

int getline(char *s);
int strend(char *s, char *t);

/* 编写函数strend(s, t)。如果字符串t出现在字符串s的尾部，该函数返回1；否则返回0。 */
int main()
{
    char s[MAXLEN], t[MAXLEN];
    printf("type string s:");
    getline(s);
    printf("type string t:");
    getline(t);
    printf("If t is at end of s?\n%s!", strend(s, t)? "YES": "NO");
}

int getline (char *s)
{
    int c;
    while((c = getchar()) != EOF && c != '\n')
        *s++ = c;
    *s = '\0';
    return strlen(s);
}

/* strend: t is at end of s; s must be big enough */
int strend(char *s, char *t)
{
    while(*s != *t && *s != '\0')
        s++;
    while(*s == *t && *s != '\0')
    {
        s++;
        t++;
    }
    if (*s == '\0' && *t == '\0')
        return 1;
    else
        return 0;
}
