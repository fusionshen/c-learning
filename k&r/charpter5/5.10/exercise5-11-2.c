#include <stdio.h>
#include <stdlib.h>

#define     MAXLINE     100     //一行字符串的最大长度
#define     TABINC      8       //默认地制表符停止位
#define     YES         1       //标记是否遇到制表符停止位
#define     NO          0

void settab(int argc, char** argv, char* tab);
void detab(char* tab);
int tabpos(int pos, char* tab);

/*
* 修改程序entab和detab(第一章练习中编写的函数)，使他们接受一组作为参数的制表符停止位。
* 如果启动程序时不带参数，则使用默认的制表符停止位设置。
* 该程序为改写detab
*/
int main(int argc, char* argv[])
{
    char tab[MAXLINE+1];        //标识一行字符串中哪些位是制表符停止位，
                                //数组tab中的每一个元素对应这文本行的一个位置(tab[0]不用)
    settab(argc, argv, tab);
    detab(tab);

    return 0;
}

/*settab：设置一行字符中哪些位是停止位，哪些位不是*/
void settab(int argc, char* argv[], char* tab)
{
    int i;
    int pos;                    //程序在当前文本行的位置

    if(argc <= 1)
        for(i = 1; i <= MAXLINE; ++i)
            if(i % TABINC == 0) //每隔8个字符设置一个停止位(即tab[i%TABINC] = YES)
                tab[i] = YES;
            else
                tab[i] = NO;
    else
    {
        for(i = 1; i <= MAXLINE; ++i)
            tab[i] = NO;
        while(--argc > 0)
        {
            pos = atoi(*++argv);
            if(pos > 0 && pos <= MAXLINE)
                tab[pos] = YES;
        }
    }
}

/*detab：将'\t'用相应的空格代替(综合argv中的参数)*/
void detab(char* tab)
{
    int c;
    int pos;

    pos = 1;
    while((c = getchar()) != EOF)
        if(c == '\t')           //当c='\t'时，在遇到下一个停止位前，用空格填充之
            do
                putchar(' ');
            while(tabpos(pos++, tab) != YES);
        else if(c == '\n')
        {
            putchar(c);
            pos = 1;
        }
        else
        {
            putchar(c);
            ++pos;
        }
}

/*tabpos：判读某个位置是否是一个制表符停止位*/
int tabpos(int pos, char* tab)
{
    if(pos > MAXLINE)            //如果pos大于MAXLINE，则返回YES，表示终止
        return YES;
    else
        return tab[pos];
}
