#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000 /* maximum input line length */
#define MAXLENGTH 0 /* maximum input every single line length */
#define EMPTYSPACESIZE 7 /* table equals 7 empty spaces */

int getline(char line[], int maxline);
void copy(char to[], char from[]);
void detab(char from[],char to[]);

/* 编写程序detab，将输入中的制表符替换成适当数目的空格，使空格充满到下一个制表符
* 终止位的地方。假设制表符终止位的位置是固定的，比如每隔n'列就会出现一个制表符终止
* 位。n应该作为变量还是符号常量呢？ */
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
    char newlines[MAXLINE][MAXLINE];
    do {
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
        detab(targetlines[j], newlines[j]);
        printf("%s", newlines[j]);
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

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

/* 遇到制表符即替换适当数目的空格
* 即碰到空格就要1位变7位 */
void detab(char from[],char to[])
{
    int i,j,k;
    i = 0;
    while(from[i] != '\0')  /* find the end of string s 求字符串长度包含了\n */
        ++i;
    j = 0;
    k = 0;
    while(j < i)
    {
        if(from[j] == '\t')
        {
            for (int m = 0; m < EMPTYSPACESIZE; ++m)
            {
                to[k] = ' ';
                ++k;
            }
        }
        else
        {
            to[k] = from[j];
            ++k;
        }
        ++j;
    }
}
