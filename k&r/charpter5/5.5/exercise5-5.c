#include <stdio.h>
#include <string.h>
#define MAXLEN 100

int getline(char *s);
void mstrncopy(char *s, char *t, int n);
void mstrncat(char *s, char *t, int n);
int mstrncmp(char *s, char *t, int n);

/*
** 实现库函数strncopy、strncat和strncmp，它们最多对参数字符串中的前n个字符进行操作。例如，函数strncopy(s, t, n)将t
** 中最多前n个字符复制到s中。更详细的说明请参见附录B。
** type string s:1234567
** type string t:abcdefg
** string s after strncopy(s,t,4):abcd567
** string s after mstrncat(s,t,4):abcd567abcd
** if s equals t with pre 4 characters? YES!
*/
int main()
{
    char s[MAXLEN], t[MAXLEN];
    printf("type string s:");
    getline(s);
    printf("type string t:");
    getline(t);
    int n = 4;
    mstrncopy(s, t, n);
    printf("string s after strncopy(s,t,%d):%s\n", n, s);
    mstrncat(s, t, n);
    printf("string s after mstrncat(s,t,%d):%s\n", n, s);
    printf("if s equals t with pre %d characters? %s\n", n, mstrncmp(s, t, n) ? "NO!" : "YES!");
}

int getline (char *s)
{
    int c;
    while((c = getchar()) != EOF && c != '\n')
        *s++ = c;
    *s = '\0';
    return strlen(s);
}

void mstrncopy(char *s, char *t, int n)
{
    int i = 0;
    while(i < n && (*s++ = *t++))
        i++;
}

/* strncat: concatenate n t to end of s; s must be big enough */
void mstrncat(char *s, char *t, int n)
{
    while(*s != '\0')
        s++;
    int i = 0;
    while(i < n &&(*s++ = *t++))
        i++;
    if(*t != '\0')
        *s = '\0';
}


/* strncat:  return <0 if s<t, 0 if s==t, >0 if s>t */
int mstrncmp(char *s, char *t, int n)
{
    for (int i = 0; *s == *t && i < n - 1; s++, t++, i++) /* 就是要比四次0，1，2，3 */
        if (*s == '\0')
            return 0;
    return *s - *t;
 }

