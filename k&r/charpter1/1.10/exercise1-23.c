/*
 *Copyright (C) Zhang Haiba
 *Date 2014-02-26
 *File exercise1_23.c
 *
 *this program removes all comments in grammatical C code,
 *and as a integrity solution for exercise1-23 in <>
 */

/*
@Link: http://www.cnblogs.com/zhanghaiba/p/3569928.html

http://blog.csdn.net/yuezhiren/article/details/7957823



以下为转载该题在状态机编程思想下详细解答过程

00）设正常状态为0，并初始为正常状态

每遍历一个字符，就依次检查下列条件，若成立或全部检查完毕，则回到这里检查下一个字符

01）状态0中遇到/，说明可能会遇到注释，则进入状态1　　　　　　　　　　ex. int a = b; /

02）状态1中遇到*，说明进入多行注释部分，则进入状态2　　　　　　　　　ex. int a= b; |*

03）状态1中遇到/，说明进入单行注释部分，则进入状态4　　　　　　　　　ex. int a = b; //

04）状态1中没有遇到*或/，说明/是路径符号或除号，则恢复状态0　　　　  ex. <secure/_stdio.h> or 5/3

05）状态2中遇到*，说明多行注释可能要结束，则进入状态3　　　　　　　　ex. int a = b; |*heh*

06）状态2中不是遇到*，说明多行注释还在继续，则维持状态2　　　　　　　ex. int a = b; |*hehe

07）状态3中遇到/，说明多行注释要结束，则恢复状态0　　　　　　　　　　ex. int a = b; |*hehe*|

08）状态3中不是遇到/，说明多行注释只是遇到*，还要继续，则恢复状态2 　ex. int a = b; |*hehe*h

09）状态4中遇到\，说明可能进入折行注释部分，则进入状态9　　　　　　　ex. int a = b; //hehe\

10）状态9中遇到\，说明可能进入折行注释部分，则维护状态9　　　　　　　ex. int a = b; //hehe\\\

11）状态9中遇到其它字符，则说明进入了折行注释部分，则恢复状态4　　　 ex. int a = b; // hehe\a or hehe\<enter>

12）状态4中遇到回车符\n，说明单行注释结束，则恢复状态0 　　　　　　　ex. int a = b; //hehe<enter>

13）状态0中遇到'，说明进入字符常量中，则进入状态5 　　　　　　　　　　ex. char a = '

14）状态5中遇到\，说明遇到转义字符，则进入状态6　　　　　　　　　　　ex. char a = '\

15）状态6中遇到任何字符，都恢复状态5 　　　　　　　　　　　　　　　　ex. char a = '\n 还有如'\t', '\'', '\\' 等 主要是防止'\''，误以为结束

16）状态5中遇到'，说明字符常量结束，则进入状态0　　　　 　　　　　　　ex. char a = '\n'

17）状态0中遇到"，说明进入字符串常量中，则进入状态7　　　　　　　　　ex. char s[] = "

18）状态7中遇到\，说明遇到转义字符，则进入状态8　　　　　　　　　　　ex. char s[] = "\

19）状态8中遇到任何字符，都恢复状态7　　　　　　　　　　　　　　　 　ex. char s[] = "\n 主要是防止"\"，误以为结束

20）状态7中遇到"字符，说明字符串常量结束，则恢复状态0　　　　　　　　ex. char s[] = "\"hehe"

前面说过，不同状态可以有相应的动作。比如状态0、5、6、7、8都需要输出当前字符，再考虑一些特殊情况就可以了。

读者实现时可以借助debug宏定义，将测试语句输出到标准错误输出，需要时可以重定位到标准输出，即2>&1，然后通过重定向|到more进行查看。
*/

#include <stdio.h>
#define debug
//#define debug(fmt, args...) fprintf(stderr, fmt, ##args)

void dfa();

int main(void)
{
    dfa();
    return 0;
}

void dfa()
{
    int c, state;

    state = 0;
    while ((c = getchar()) != EOF) {
        if (state == 0 && c == '/')         // ex. [/]
            state = 1;
        else if (state == 1 && c == '*')     // ex. [/*]
            state = 2;
        else if (state == 1 && c == '/')    // ex. [//]
            state = 4;
        else if (state == 1) {                // ex. [ or 5/3]
            putchar('/');
            state = 0;
        }

        else if (state == 2 && c == '*')    // ex. [/*he*]
            state = 3;
        else if (state == 2)                // ex. [/*heh]
            state = 2;

        else if (state == 3 && c == '/')    // ex. [/*heh*/]
            state = 0;
        else if (state == 3)                // ex. [/*heh*e]
            state = 2;

        else if (state == 4 && c == '\\')    // ex. [//hehe\]
            state = 9;
        else if (state == 9 && c == '\\')    // ex. [//hehe\\\\\]
            state = 9;
        else if (state == 9)                // ex. [//hehe\ or //hehe\a]
            state = 4;
        else if (state == 4 && c == '\n')    // ex. [//hehe]
            state = 0;

        else if (state == 0 && c == '\'')     // ex. [']
            state = 5;
        else if (state == 5 && c == '\\')     // ex. ['\]
            state = 6;
        else if (state == 6)                // ex. ['\n or '\' or '\t etc.]
            state = 5;
        else if (state == 5 && c == '\'')    // ex. ['\n' or '\'' or '\t' ect.]
            state = 0;

        else if (state == 0 && c == '\"')    // ex. ["]
            state = 7;
        else if (state == 7 && c == '\\')     // ex. ["\]
            state = 8;
        else if (state == 8)                // ex. ["\n or "\" or "\t ect.]
            state = 7;
        else if (state == 7 && c == '\"')    // ex. ["\n" or "\"" or "\t" ect.]
            state = 0;

        //debug("c = %c, state = %d\n", c, state);

        if ((state == 0 && c != '/') || state == 5 || state == 6 || state == 7 || state == 8)
            putchar(c);
    }
}