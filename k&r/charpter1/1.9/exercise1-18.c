#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000 /* maximum input line length */
#define MAXLENGTH 0 /* maximum input every single line length */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* 编写一个程序，删除每个输入行末尾的空格及制表符，并删除完全是空格的行 */
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

    printf("the new text is:\n");
    for (int j = 0; j < i; ++j)
        printf("%s", targetlines[j]);

    if (max > 0) /* there was a line */
        printf("%d\t%s", max, longest);

    return 0;
}

/* getline: read a line into s return length
*  delete empty spaces and tables at end of each line
*  delete empty lines
*/
int getline(char s[], int lim)
{
    int c, i, k;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        // 从数组最后一个字符开始往前循环判断，符合空格或制表符，就继续循环，直到不符合条件后跳出，然后加入终止符。
        for (k = i; s[k]==' ' || s[k]=='\t'; --k)
            ;
        //if(k != 0) //这种情况保证空行也能够被录入,
        //sfs2020年2月23日一定注意空行也是有长度(\n)的，长度为1。
        i = k;
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