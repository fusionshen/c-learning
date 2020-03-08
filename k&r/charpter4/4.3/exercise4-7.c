#include <stdio.h>
#include <string.h>

#define MAXLEN 100
#define BUFSIZE 100


int getch(void);
void ungetch(int);
void ungets(char s[]);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/* 编写一个函数ungets(s)，讲整个字符串s压回到输入中。ungets函数需要使用buf和bufp吗？它能否仅使用ungetch函数？ */
int main()
{
    int i = 0;
    int c;
    char s[MAXLEN];
    printf("type you string:\n");
    while((c = getchar()) != '\n' && i < MAXLEN)
        s[i++] = c;
    s[i] = '\0';
    ungets(s);
    while ((c = getch()) != EOF)
        printf("%c\n", c);
    return 0;
}

int getch(void) /* get a (prossibly pushed-back) charactor */
{
    if (bufp > 0) {
        int c = buf[--bufp];
        printf("取回%c\n", c);
        return c;
    }
    else
        return getchar();
    //return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZ)
        printf("ungetch: too many characters\n");
    else {
        printf("压入%c\n", c);
        buf[bufp++] = c;
    }

}

void ungets(char s[])
{
    size_t l = strlen(s);
    while (l > 0)
        ungetch(s[--l]);
}
