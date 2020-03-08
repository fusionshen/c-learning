#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXLEN 100

void push(double);
double pop(void);
int isempty(void);

double var[26]; /* A-Z's value, must upper */
double prev = 0.0; /* v: pre print val */

int getline(char s[], int lim);

/* 另一种方法是通过getline函数读入整个输入行，这种情况下可以不使用getch与ungetch函数。请运用这一方法修改计算器程序。 */
/* reverse polish calculator */
int main()
{
    int type = EOF;
    double op2;
    char t[MAXLEN];
    char s[MAXOP];
    int pret = EOF; /* pre type */

    for (int i = 0; i < 26; i++)
        var[i] = 0.0;

    do
    {
        if (getline(t, MAXLEN) == 0)
            break;

        int i, c;
        i = 0;
        while (i < strlen(t))
        {
            c = t[i];
            if (c != ' ' && c != '\t')
            {
                s[0] = c;
                s[1] = '\0';
                if (!isdigit(c) && c != '.' && c != '-')
                {
                    type = c; /* not a number */
                    ++i;
                }
                int j = 0;
                if (c == '-') {
                    if (!isdigit(t[++i]))
                        type = '-';  /* just - */
                    else
                        s[++j] = c = t[i];
                }
                if (isdigit(c)) {
                    /* collect integer part */
                    while (isdigit(s[++j] = c = t[++i]))
                        ;
                    if (c == '.') /* collect fraction part*/
                        while (isdigit(s[++j] = c = t[++i]))
                            ;
                    s[j] = '\0';
                    type = NUMBER;
                }
                switch (type)
                {
                case NUMBER:
                    push(atof(s));
                    break;
                case '+':
                    push(pop() + pop());
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case '-':
                    op2 = pop();
                    push(pop() - op2);
                    break;
                case '/':
                    op2 = pop();
                    if (op2 != 0.0)
                        push(pop() / op2);
                    else
                        printf("error: zero divisor\n");
                    break;
                case '%':
                    op2 = pop();
                    if (op2 != 0.0)
                        push((int)pop() % (int)op2);
                    else
                        printf("error: zero mod\n");
                    break;
                case 's': /* sin */
                    push(sin(pop()));
                    break;
                case 'e': /* exp */
                    push(exp(pop()));
                    break;
                case 'p': /* pow */
                    op2 = pop();
                    push(pow(pop(), op2));
                    break;
                case '\n':
                    if (!isempty())
                    {
                        prev = pop();
                        printf("\t%.8g\n", prev);
                    }
                    break;
                case '=':
                    if(isupper(pret)) {
                        pop();
                        var[pret - 'A'] = pop();
                        printf("\t%c = %g\n", pret, var[pret - 'A']);
                    }
                    else
                        printf("error: wrong variable\n");
                    break;
                default:
                    if (isalpha(type)) /* A-Z & v */
                    {
                        if (type == 'v')
                            push(prev);
                        else if (isupper(type))
                            push(var[type - 'A']);
                        else
                            printf("error: wrong variable\n");
                    }
                    else
                        printf("error: unknown command %s\n", s);
                    break;
                }
                pret = type;
            }
            else
            {
                i++;
            }
        }
    } while (1);
    return 0;
}

#define MAXVAL 100 /* maximun depth of val stack */

int sp = 0; /* next free stack positon */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* isempty: stack is empty */
int isempty(void)
{
    return sp == 0;
}

/* getline: get line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
