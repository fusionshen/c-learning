#include <stdio.h>
#include <string.h>
#define MAXLINE 1000 /* maximum input line length */
#define MAXLENGTH 0 /* maximum input every single line length */
#define EMPTYSPACESIZE 7 /* table equals 7 empty spaces */

int getline(char line[], int maxline);
void copy(char to[], char from[]);
void entab(char from[], char to[]);

/* 编写程序entab，将空格串替换为最少数量的制表符和空格，但要保持单词之间的间隔不变。假设制表符
* 终止位的位置与练习1-20的detab程序的情况相同。当使用一个制表符或者一个空格可以到达下一个制表符
* 终止位时，选用哪一种替换字符比较好 */
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
    char enlines[MAXLINE][MAXLINE];

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
        entab(targetlines[j], enlines[j]);
        printf("%s", enlines[j]);
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

/* 1.遇到制表符即替换适当数目的空格
* 即碰到空格就要1位变7位
* 2.遇到空格即替换适当数目的制表符 */
void entab(char from[],char to[])
{
    int i,j,k;
    i = 0;
    while(from[i] != '\0')  /* find the end of string s 求字符串长度包含了\n */
        ++i;
    j = 0;
    k = 0;
    char mid[MAXLINE];
    while(j < i)
    {
        if(from[j] == '\t')
        {
            for (int m = 0; m < EMPTYSPACESIZE; ++m)
            {
                mid[k] = ' ';
                ++k;
            }
        }
        else
        {
            mid[k] = from[j];
            ++k;
        }
        ++j;
    }

    int g = 0;
    for (int n = 0; n < k;)
    {
        if(mid[n] == ' ') // 碰到空格需要检测后续是否有连续EMPTYSPACESIZE-1个空格，是就替换
        {
            int temp = 1; //假设是连续的空格
            for (int m = 0; m < EMPTYSPACESIZE; ++m)
            {
                if (mid[n + m] != ' ') {
                    temp = 0;
                    break;
                }
            }
            if (temp == 1) {
                to[g] = '\t';
                ++g;
                n += EMPTYSPACESIZE;
            }
            else
            {
                to[g] = mid[n];
                ++g;
                ++n;
            }
        }
        else
        {
            to[g] = mid[n];
            ++g;
            ++n;
        }

    }

}
