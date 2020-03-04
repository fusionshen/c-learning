#include <stdio.h>
#include <string.h>

#define MAXLINE 1000 /* maximum input line length */

int getline(char line[], int maxline);
void copy(char to[], char from[]);
void escape(char s[], char t[]);
void deescape(char s[], char t[]);

/*
** 编写一个函数escape(s, t),将字符串t复制到字符串s中，并在复制过程中将换行符、制表符等不可见字符分别转换成\n、
** \t等相应的可见的转义字符序列。要求使用switch语句。再编写一个具有相反功能的函数，在复制过程中将转义字符序列
** 转换为实际字符。
*/
int main()
{
    int len; /* current line length */
    int prelen = 0; /* pre line lenth */
    int i = 0;
    char line[MAXLINE];
    char preline[MAXLINE];
    char targetlines[MAXLINE][MAXLINE];
    char result[MAXLINE];
    char result1[MAXLINE];
    printf("please type origin string(end it with Ctrl+Z):");
    do {
        len = getline(line, MAXLINE);
        if (len ==0)
            break;
        if (prelen ==0)
            copy(preline, line);

        if (len == MAXLINE - 1 && line[MAXLINE - 1] != '\n') {
            prelen += len;
            len += prelen;
        }
        else
            prelen = 0;
        if (len > 0)
            copy(targetlines[i++], line);
    } while (1);

    for (int j = 0; j < i; j++)
        escape(result, targetlines[j]);

    printf("the new string after running escape function is:%s\n", result);
    deescape(result1, result);
    printf("the new string after running deescape function is:%s\n", result1);
}

/* getlien: read aline into s return length */
int getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

void escape(char s[], char t[])
{
    for (int i = 0, pos = strlen(s); i < strlen(t); i++)
    {
        switch (t[i])
        {
            case '\n':
                s[pos++] = '\\';
                s[pos++] = 'n';
                break;
            case '\t':
                s[pos++] = '\\';
                s[pos++] = 't';
                break;
            default:
                s[pos++] = t[i];
                break;
        }
    }
}

// 状态机
void deescape(char s[], char t[])
{
    int state = 0;
    for (int i = 0, pos = strlen(s); i < strlen(t); i++)
    {
        switch (t[i])
        {
            case '\\':
                s[pos++] = '\\';
                state = 1;
                break;
            case 'n':
                switch (state)
                {
                    case 0:
                        s[pos++] = t[i];
                        break;
                    case 1:
                        s[--pos] = '\n'; // 减完还需要往后移一位
                        pos++;
                        break;
                    default:
                        break;
                }
                state = 0;
                break;
            case 't':
                switch (state)
                {
                    case 0:
                        s[pos++] = t[i];
                        break;
                    case 1:
                        s[--pos] = '\t';
                        pos++;
                        break;
                    default:
                        break;
                }
                state = 0;
                break;
            default:
                s[pos++] = t[i];
                state = 0;
                break;
        }
    }

}



