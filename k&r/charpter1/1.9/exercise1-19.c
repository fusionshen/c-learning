#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000 /* maximum input line length */
#define MAXLENGTH 0 /* maximum input every single line length */

int getline(char line[], int maxline);
void copy(char to[], char from[]);
void reverse(char s[]);

/* 编写函数reverse(s),将字符串s中的字符顺序颠倒过来。编写一个程序，每次颠倒一个输入行中的字符顺序。 */
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

        // delete empty lines
        if (len > MAXLENGTH) {
            copy(targetlines[i], line); /* copy(targetlines[++i], line) is wrong */
            ++i;
        }

    } while (1);

    printf("the newly reversed text is:\n");
    for (int j = 0; j < i; ++j) {
        reverse(targetlines[j]);
        printf("%s", targetlines[j]);
    }

    if (max > MAXLENGTH) /* there was a line */
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

/* reverse: reverse strings  */
void reverse(char s[])
{
    int i,j;
    char temp;

    i = 0;
    while(s[i] != '\0')  /* find the end of string s */
        ++i;
    --i;                /* back off from '\0'  */
    if(s[i] == '\n')  /* 转行是不用倒置的 */
        --i;            /* leave newline in place  */
    j = 0;
    while(j < i)
    {
        temp = s[j];
        s[j] = s[i];    //swap the characters
        s[i] = temp;
        --i;
        ++j;
    }
}
