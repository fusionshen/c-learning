#include <stdio.h>
int brace, brack, paren;
void in_quote(int c);
void in_comment(void);
void search(int c);
/* C语言程序初步的语法检查 */
int main()
{
    int c;
    extern int brace, brack, paren;
    while ((c = getchar()) != EOF) {
        if (c == '/') {
            if ((c = getchar()) == '*')
                in_comment();   /* 评论内 */
            else
                search(c);
        } else if (c == '\'' || c == '"')
            in_quote(c);    /* 引用内 */
        else
            search(c);
        if (brace < 0) {    /* 输出错误 */
            printf("Unbalanced braces\n");  /* 大括号 */
            brace = 0;
        } else if (brack < 0) {
            printf("Unbalanced brackets\n");    /* 方括号 */
            brack = 0;
        } else if (paren < 0) {
            printf("Unbalanced parentheses\n"); /* 圆括号 */
            paren = 0;
        }
    }
    if (brace > 0)  /* 输出错误 */
        printf("Unbalanced braces\n");
    if (brack > 0)
        printf("Unbalanced brackets\n");
    if (paren > 0)
        printf("Unbalanced parenthess\n");
}
/* search函数：搜索一个基本语法错误 */
void search(int c)
{
    extern int brace, brack, paren;
    if (c == '{')
        ++brace;
    else if (c == '}')
        --brace;
    else if (c == '[')
        ++brack;
    else if (c == ']')
        --brack;
    else if (c == '(')
        ++paren;
    else if (c == ')')
        --paren;
}
/* in_comment函数：在一个有效的注释内 */
void in_comment(void)
{
    int c, d;
    c = getchar();  /* 上一个字符 */
    d = getchar();  /* 目前的字符 */
    while (c != '*' || d != '/') {  /* 搜索结束标志 */
        c = d;
        d = getchar();
    }
}
/* 在引用内 */
void in_quote(int c)
{
    int d;
    while ((d = getchar()) != c) {  /* 搜索结束标志 */
        if (d == '\\')
            getchar();
    }
}