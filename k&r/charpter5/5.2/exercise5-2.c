#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100
#define SIZE 100

int getch(void);
void ungetch(int);

/*
** 模仿函数getint的实现方法，编写一个读取浮点数的函数getfloat。
** getfloat函数的返回值应该是什么类型？
*/
int main()
{
    int n;
    double array[SIZE], getfloat(double *);
    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        ;
    printf("array:");
    for (int i = 0; i < n; i++)
        printf("%g ", array[i]);
}

/* getfloat: get next float from input double *pn */
double getfloat(double *pn)
{
    int c, sign;
    double power;

    while (isspace(c = getch())) /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c!= '+' && c !='-') {
        ungetch(c);
        return 0.0;
    }
    sign = (c == '-') ? -1 : 1;
    int temp;
    if ((temp = c) == '+' || (temp = c) == '-') {
        c = getch();
        if(!isdigit(c))
            ungetch(temp);
        while (!isdigit(c = getch())) /* skip no numberic */
            ;
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    if(c == '.')
        c = getch();
    for (power = 1.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
        power *= 10;
    }
    *pn = sign * *pn / power;
    //e-6
    if (c == 'e' || c == 'E') {
        c = getch();
        int sign1 = 1;
        if (c == '+')
            c = getch();
        else if (c == '-') {
            sign1 = -1;
            c = getch();
        }
        int e = 0;
        for (; isdigit(c); c = getch())
            e = 10 * e + (c - '0');
        for (int m = 0; m < e; m++)
            *pn *= (sign1 == 1) ? 10.0 : 0.1;
    }
    if ( c != EOF)
        ungetch(c);
    return c;
}

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (prossibly pushed-back) charactor */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZ)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
