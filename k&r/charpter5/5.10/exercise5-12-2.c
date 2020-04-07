#include <stdio.h>
#include <stdlib.h>

#define     MAXLINE     100     //一行字符串的最大长度
#define     TABINC      8       //默认地制表符停止位
#define     YES         1       //标记是否遇到制表符停止位
#define     NO          0

void settab(char* tab, int start, int block);
void detab(char* tab);
int tabpos(int pos, char* tab);

/*
* 对程序entab和detab的功能做一些扩充，以接受下列缩写的命令：
* entab -m +n
* 表示制表符从第m列开始，每隔n列停止。选择（对使用者而言）比较方便的默认行为。
* 该程序为改写detab
*/
int main(int argc, char* argv[])
{
    char tab[MAXLINE+1];        //标识一行字符串中哪些位是制表符停止位，
                                //数组tab中的每一个元素对应这文本行的一个位置(tab[0]不用)
    int c, start = 0, block = 0;

    while(--argc > 0 && ((c = **++argv) == '-' || c == '+'))
		switch (c){
		case '-':
			start = atoi(*argv+1);
			break;
		case '+':
			block = atoi(*argv+1);
			break;
		default:
			printf("find: illegal option %c\n", c);
			argc = 0;
			break;
		}

    printf("m=%d,n=%d\n", start, block);

    settab(tab, start, block);
    detab(tab);

    return 0;
}

/*settab：设置一行字符中哪些位是停止位，哪些位不是*/
void settab(char* tab, int start, int block)
{
    int j = block == 0 ? TABINC : block;
    for(int i = start; i <= MAXLINE; ++i)
        if(i % j == 0) //每隔8个字符设置一个停止位(即tab[i%TABINC] = YES)
            tab[i] = YES;
        else
            tab[i] = NO;
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
