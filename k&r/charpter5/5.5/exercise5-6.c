#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define MAXLINE 100
#define BUFSIZE 100
#define NUMBER '0' /* signal that a number was found */


int getline_charpter_1(char *s, int lim);
int getline_charpter_4(char *s, int lim);
int atoi_charpter_2(char *s);
int atoi_charpter_3(char *s);
void itoa_charpter_3(int n, char *s);
void reverse_charpter_3(char *s);
void itoa_charpter_3_exercise(int n, char *s);
void itoa_charpter_4(int n, char **s);
int strindex(char *s, char *t);
int getch(void);
int getop(char *s);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/*
** 采用指针而非数组索引方式改写前面章节和练习中的某些程序，例如getline(第1、4章)，atoi、itoa以及它们的变体形式
** （第2、3、4章），reverse（第3章），strindex、getop（第4章）等等。
*/
int main()
{
    int n = INT_MIN;
    char s[MAXLINE];
    printf("type string to int with getline function in charpter 1: ");
    getline_charpter_1(s, MAXLINE);
    printf("the resule after running atoi function in charpter 2: %d\n", atoi_charpter_2(s));
    printf("the resule after running atoi function in charpter 3: %d\n", atoi_charpter_3(s));
    char t[MAXLINE];
    char *ps = t;
    itoa_charpter_3(-123456, t);
    printf("-123456 after running itoa function in charpter 3: %s\n", t);
    itoa_charpter_3(n, t);
    printf("min int after running itoa function in charpter 3: %s\n", t);
    itoa_charpter_3_exercise(-123456, t);
    printf("-123456 after running itoa function in charpter 3 exercise: %s\n", t);
    itoa_charpter_3_exercise(n, t);
    printf("min int after running itoa function in charpter 3 exercise: %s\n", t);
    itoa_charpter_4(-123456, &ps);
    printf("-123456 after running itoa function in charpter 4: %s\n", t);
    ps = t;
    itoa_charpter_4(n, &ps);
    printf("min int after running itoa function in charpter 4: %s\n", t);
    printf("type string t with getline function in charpter 4:");
    getline_charpter_4(t, MAXLINE);
    printf("If string t firstly appear in string s at: %d\n", strindex(s, t));
}

int getline_charpter_1 (char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        *s++ = c;
    if (c == '\n')
        *s++ = '\n';
    *s = '\0';
    return i;
}

int getline_charpter_4 (char *s, int lim)
{
    int c, i = lim;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = '\n';
    *s = '\0';
    return i - lim;
}

int atoi_charpter_2(char *s)
{
    int n = 0;
    for (; *s >= '0' && *s <= '9'; s++)
        n = 10 * n + (*s - '0');
    return n;
}

int atoi_charpter_3(char *s)
{
    int n = 0, sign;
    while (isspace(*s))
        s++;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (; *s >= '0' && *s <= '9'; s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}

// -2147483648
void itoa_charpter_3(int n, char *s)
{
    char *p = s;
    int sign;
    if((sign = n) < 0)
        n = -n;
    do {
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse_charpter_3(p);
}

void reverse_charpter_3(char *s)
{
    char *p, *q, c;
    p = q = s;
    while(*p) p++;
    p--;
    while( q < p)
    {
        c = *p;
        *p = *q;
        *q = c;
        q++;
        p--;
    }
}

void itoa_charpter_3_exercise(int n, char *s)
{
    char *p = s;
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
        *s++ = n_copy % 10 + '0';
    } while ((n_copy /= 10) > 0);
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse_charpter_3(p);
}

//-2147483648
//https://www.cnblogs.com/oshyn/p/4807302.html
void itoa_charpter_4(int n, char  **s)
{
    int sign = n;
    unsigned n_copy;
    if ((sign = n) < 0) {
        if((n-1) > 0)
            n_copy = n;
        else {
            **s = '-';
            (*s)++;
            n_copy = -n;
        }
    } else
        n_copy = n;

    if (n_copy/10)
        itoa_charpter_4(n_copy/10, s);

    **s = n_copy % 10 + '0';
    (*s)++;
    **s = '\0';
}

int strindex(char *s, char *t)
{
    for (int i = 0; *s != '\n'; i++, s++)
    {
        char *q;
        char *p;
        for (q = s, p = t; *p != '\n' && *q == *p; q++, p++)
            ;
        if (*p == '\n')
            return i;
    }
    return -1;
}

int getch(void) /* get a (prossibly pushed-back) charactor */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

int getop(char *s)
{
    static int c;

    while ((*s = c = getch()) == ' ' || c == '\t')
        ;
    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* not a number */

    if (c == '-') /* maybe a number */
    {
        s++;
        *s = c = getch();
    }
    if (isdigit(c))  /* collect integer part */
        while (isdigit(*s++ = c = getch()))
            ;
    if (c == '.') /* collect fraction part*/
        while (isdigit(*s++ = c = getch()))
            ;
    *s = '\0';
    if (*s-- == '-')
        return '-'; /* just - */
    return NUMBER;
}
