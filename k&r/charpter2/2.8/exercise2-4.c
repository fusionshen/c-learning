#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

void squeeze(char s1[], char s2[]);
void squeeze1(char s1[], char s2[]);
int getline(char s[], int lim);

/* squeeze1(s1,s2),将字符串s1中任何与字符串s2中字符匹配的字符都删除
** 题意理解错误，squeeze(s1,s2)是将字符串s1中的任何字符串s2删除
*/

int main()
{
    char s1[MAXLINE];
    char s2[MAXLINE];
    printf("input s1: ");
    getline(s1, MAXLINE);
    printf("input s2: ");
    getline(s2, MAXLINE);
    squeeze1(s1, s2);
    printf("the new s1 is %s", s1);
}

/* squeeze:  delete all s2 from s1 */
void squeeze(char s1[], char s2[])
{
    int i, j, k;
    int temp;  // 是否匹配
    for (i = k = 0; s1[i] != '\0';)
    {
        temp = 1;
        j = 0;
        for (int m = i; s2[j] != '\0'; j++)
            if (s1[m] != s2[j])
            {
                temp = 0;
                break;
            }
            else
                ++m;
        // 存在 j = 0的特殊情况
        if (temp == 0 || j == 0)
            s1[k++] = s1[i++];
        else
            i += j;

    }
    s1[k] = '\0';
}

void squeeze1(char s1[],char s2[])
{
    int i, j, k;
    for(i = k =0; s1[i] != '\0'; i++)
    {
        for(j = 0; s2[j] != '\0' && s2[j] != s1[i]; j++)
            ;
        if(s2[j] == '\0')
            s1[k++] = s1[i];
    }
    s1[k] = '\0';
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
