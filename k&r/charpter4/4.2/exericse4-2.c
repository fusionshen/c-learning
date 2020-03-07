#include <stdio.h>
#include <ctype.h>
#define MAXLINE 100

/*
** 对atof函数进行扩充，使他可以处理形如
** 123.45e-6
** 的科学表示法，其中，浮点数后面可能会紧跟一个e或E以及一个指数（可能有正负号）
 */

int main()
{
    double atof(char[]);
    char line[MAXLINE];
    int getline(char line[], int max);

    while (getline(line, MAXLINE) > 0)
        printf("\t%g\n", atof(line));
    return 0;
}

/* atof: convert string s to double */
double atof(char s[])
{
    double val, power;
    int i, sign;
    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    val = sign * val / power;
    //e-6
    if (s[i] == 'e' || s[i] == 'E')
    {
        i++;
        int sign1 = 1;
        if (s[i] == '+')
            i++;
        else if (s[i] == '-') {
            sign1 = -1;
            i++;
        }
        int e = 0;
        for (; isdigit(s[i]); i++)
            e = 10 * e + (s[i] - '0');
        for (int m = 0; m < e; m++)
            val *= (sign1 == 1) ? 10 : 0.1;
    }
    return val;
}

/* getline: get line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
