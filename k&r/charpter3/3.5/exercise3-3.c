#include <stdio.h>
#include <string.h>

#define MAXLINE 1000 /* maximum input line length */
void expand(char s1[], char s2[]);
int replace(char s1[], int start, int end, int i);

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
    printf("the origin string is:%s\n", s);
    expand(result, s);
    printf("the new string expanded is:%s\n", result);
}

/*
** 状态机，s2每次向右移位1步
** 1.初始状态为0
** 2.状态0碰到a-z0-9A-Z中某一个进入状态1，并将该字符移入s1，并将当前字符记为pre
** 3.状态0碰到-进入状态0，并将该字符移入s1，清除pre
** 4.状态0碰到其它字符(有别于2和3情况)进入状态0，并将该字符移入s1，清除pre
** 5.状态1(情况2)碰到-进入状态2，表示有可能需要扩展打印，并将该字符移入s1(如果扩展打印后面会将其移出)
** 6.状态1碰到a-z0-9A-Z中某一个进入状态1，并将该字符移入s1，并将其为记录pre
** 7.状态1碰到其它字符(有别于5和6中情况)进入状态0，并将该字符移入s1，清除pre
** 8.状态2(情况5)碰到匹配字符(具体为pre为a-z时，该字符值应大于等于‘pre’且小于等于‘z’，同理0-9和A-Z)
**   这是为了满足a-a，2-2，Y-Y(分别打印a，2，Y)的情形，进入状态1(情况2),这表示扩展有可能并未结束(a-c-z),
**   移出前两位字符(pre和-)，并将pre和当前字符中所有字符移入s1，并将当前字符记为pre
** 9.状态2(情况5)碰到非匹配字符（如a-z0-9A-Z）中某一个进入状态1，并将该字符移入s1，并将当前字符记为pre
** 10.状态2(情况5)碰到非匹配字符（如-）中某一个进入状态0，并将该字符移入s1，清除pre
** 11.状态2(情况5)碰到非匹配字符（如其它字符，有别于8，9，10情况）中某一个进入状态0，并将该字符移入s1，清除pre
*/
void expand(char s1[], char s2[])
{
    // 初始状态
    int state = 0;
    int pre = EOF;
    for (int i = 0, k = 0; i < strlen(s2); i++)
    {
        if (pre == EOF) {
            if (state == 0) {
                if ((s2[i] >= 'a' && s2[i] <= 'z') || (s2[i] >= '0' && s2[i] <= '9') || (s2[i] >= 'A' && s2[i] <= 'Z')) {
                    // 情况2
                    state = 1;
                    pre = s2[i];
                }
                else if (s2[i] == '-')
                    // 情况3
                    pre = EOF;
                else
                    // 情况4
                    pre = EOF;
                s1[k++] = s2[i];
            }
        } else {
            if (state == 1) {
                if ((s2[i] >= 'a' && s2[i] <= 'z') || (s2[i] >= '0' && s2[i] <= '9') || (s2[i] >= 'A' && s2[i] <= 'Z'))
                    // 情况6
                    pre = s2[i];
                else if (s2[i] == '-')
                    // 情况5
                    state = 2;
                else {
                    // 情况7
                    state = 0;
                    pre = EOF;
                }
                s1[k++] = s2[i];
            } else if (state == 2) {
                if ((s2[i] >= 'a' && s2[i] <= 'z') || (s2[i] >= '0' && s2[i] <= '9') || (s2[i] >= 'A' && s2[i] <= 'Z')) {
                    if ((pre >= 'a' && pre <= 'z' && s2[i] >= pre && s2[i] <= 'z') ||
                        (pre >= '0' && pre <= '9' && s2[i] >= pre && s2[i] <= '9') ||
                        (pre >= 'A' && pre <= 'Z' && s2[i] >= pre && s2[i] <= 'Z') ) {
                            // 情况8
                            // k = replace(s1, pre, s2[i], k); //为什么这个函数不起作用？理论上s1将k变得步调不一致
                            // a-a-a会输出a-，这是因为第二次-替换时只有一位a没办法覆盖后一位的-
                            k -= 2;
                            for (int j = pre; j <= s2[i]; j++, k++)
                                s1[k] = j;
                            }
                    else
                        // 情况9
                        s1[k++] = s2[i];
                    state = 1;
                    pre = s2[i];
                }
                else {
                    // 情况10和情况11
                    state = 0;
                    s1[k++] = s2[i];
                    pre = EOF;
                }
            }
        }
    }
}

int replace(char s1[], int start, int end, int i)
{
    printf("---->%s\n", s1);
    int j, pos;
    for (j = start, pos = i -2; j <= end; j++, pos++)
        s1[pos] = j;
    printf("<----%d,%s\n",pos, s1);
    return pos;
}

