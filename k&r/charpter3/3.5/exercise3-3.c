#include <stdio.h>
#include <string.h>

#define MAXLINE 1000 /* maximum input line length */
void expand(char s1[], char s2[]);

/*
** 编写函数expand(s1,s2)，将字符串s1中类似a-z一类的速记符号在字符串s2中扩展为等价的完整
** 列表abc...xyz。该函数可以处理大小写字母和数字，并可以处理a-b-c、a-z0-9与-a-z等类似的
** 情况。作为前导和尾随的-字符原样排印。
*/
int main()
{
    int i, c;
    char s[MAXLINE];
    char result[MAXLINE];
    printf("please type origin string(end it with key enter):");
    for (i = 0; (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    expand(result, s);
    printf("the new string expanded is:%s\n", result);
}

// 状态机
void expand(char s1[], char s2[])
{
    int state = 0;
    for (int i = 0, k = 0; i < strlen(s2);)
    {

    }
}



