#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int any(char s1[], char s2[]);
int getline(char s[], int lim);

/* 编写函数any(s1,s2)，将字符串s2中的任一字符在字符串s1中第一次出现的位置作为结果返回。
** 如果s1中不包含s2中的字符，则返回-1.(标准库函数strpbrk具有同样的功能，但它返回的是
** 指向该位置的指针。)
*/

int main()
{
    char s1[MAXLINE];
    char s2[MAXLINE];
    printf("input s1: ");
    getline(s1, MAXLINE);
    printf("input s2: ");
    getline(s2, MAXLINE);
    printf("the first postion that any char of s2 appears in s1 is %d", any(s1, s2));
}

int any(char s1[],char s2[])
{
    int i, j, k;
    for(i = k =0; s1[i] != '\0'; i++)
    {
        for(j = 0; s2[j] != '\0' && s2[j] != s1[i]; j++)
            ;
        if(s2[j] != '\0')
            return i;
    }
    return -1;
}

/* getline: read a line into s return length */
int getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    // if (c == '\n') {
    //     s[i] = c;
    //     ++i;
    // }
    s[i] = '\0';
    return i;
}
