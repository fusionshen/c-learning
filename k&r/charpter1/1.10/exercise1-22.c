#include <stdio.h>
#include <string.h>
#define MAXLINE 1000 /* maximum input line length */
#define MAXLENGTH 0 /* maximum input every single line length */
#define EMPTYSPACESIZE 7 /* table equals 7 empty spaces */
#define MAXCOL 8

int getline(char line[], int maxline);
void copy(char to[], char from[]);
void divideline(char from[]);
int findpos(char from[], int pos);

/* 编写一个程序，把较长的输入行“折”成短一些的两行或多行，折行的位置在输入行的第n列之前的
* 最后一个非空格之后。要保证程序能够智能地处理输入行很长以及在指定的列前没有空格或制表符的
* 情况 */
int main()
{
    int len; /* current line length */
    int max = 0; /* maximum length seen so far */
    int prelen = 0; /* pre line lenth */
    int i = 0;
    char line[MAXLINE];
    char longest[MAXLINE];
    char preline[MAXLINE];
    char targetlines[MAXLINE][MAXLINE];

    do{
        len = getline(line, MAXLINE);
        if (len == 0){
            break;
        }
        if(prelen == 0) { // 如果之前没有数据，说明是这一行的首次读取
            copy(preline, line);
        } // 如果不是首次读取，就不用再复制了

        if(len == MAXLINE - 1 && line[MAXLINE - 1] != '\n') { //非正常结尾
            prelen = prelen + len;
            len = prelen + len;
        }
        else
            prelen = 0;

        if (len > max) {
            max = len;
            copy(longest, line);
        }

        if (len > MAXLENGTH) {
            copy(targetlines[i], line); /* copy(targetlines[++i], line) is wrong */
            ++i;
        }

    } while (1);

    printf("the new text is:\n");
    for (int j = 0; j < i; ++j) {
        divideline(targetlines[j]);
    }


    if (max > 0) /* there was a line */
        printf("%d\t%s", max, longest);

    return 0;
}

/* getline: read a line into s return length */
int getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

/* 1.一行变成多行 */
void divideline(char from[])
{
    int i,j,k;
    i = 0;
    while(from[i] != '\0')  /* find the end of string s 求字符串长度包含了\n */
        ++i;
    k = 0;

    for (j = 0; j < i;)
    {
        if (from[j] == '\t' || from[j] == ' ')
        {
            //m即最后一个空格下标位，输入j到m并调整下标
            int m = findpos(from, j + MAXCOL - k < i ? j + MAXCOL - k : i); // 1.注意文件末尾
            for (; j < m + 1; ++j) // 2.如果不加1，会永远碰到空格进行死循环
                putchar(from[j]);
            putchar('\n');
            k = 0;
        }
        else
        {
            if (k < MAXCOL)
            {
                putchar(from[j]);
                ++k;
            }
            else
            {
                putchar('\n');
                k = 0;
                putchar(from[j]);
                ++k;
            }
            ++j;
        }

    }
}

int findpos(char from[], int pos)
{
    int m = 0;
    // 碰到空格，需要检测MAXCOL中最后一个空格后，然后调整下标
    // 3.注意退出条件，TRUE是继续循环，FALSE才是退出
    for (m = pos; from[m] != '\t' && from[m] != ' '; --m)
        ;
    return m;
}
