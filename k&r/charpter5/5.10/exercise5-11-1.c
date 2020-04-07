#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define     TABINC      8       //默认地制表符停止位
#define     MAXLINE     100     //一行字符串的最大长度

void settab(int argc, char** argv, int* tab);
void entab(char s[], int* tab);                         //定义函数entab
int tabpos(int pos, int* tab);


/*
* 修改程序entab和detab(第一章练习中编写的函数)，使他们接受一组作为参数的制表符停止位。
* 如果启动程序时不带参数，则使用默认的制表符停止位设置。
* 该程序改写entab
*/
int main(int argc, char* argv[])
{
    int tab[MAXLINE];        //标识每次出现需要转化tab时的空格数
    settab(argc, argv, tab);
	char s[MAXLINE];                         //定义一个足够大的数组
	printf("Please enter string: ");         //输入一个字符串
	gets(s);
	entab(s, tab);                           //调用entab函数
	puts(s);                            //输出变换后的字符串
}


/* settab：标识每次出现需要转化tab时的空格数 */
void settab(int argc, char* argv[], int* tab)
{
    int i;
    if(argc <= 1)
        for(i = 0; i <= MAXLINE; ++i)
            tab[i] = TABINC;
    else
    {
        for(i = 1; i <= MAXLINE; ++i)
            tab[i] = 0;
        while(--argc > 0)
            tab[argc] = atoi(*++argv);
    }
}


/*entab函数*/
void entab(char s[], int* tab)
{
	int i, j, k, len, space_count, pos = 0;              //定义变量，len是字符串长度，space_count是空格计数
	len=strlen(s);                              //测出字符串长度
	s[len]='\0';                                //给字符串加上终止符
	for (i=0, space_count=0; s[i]!='\0'; i++) {
		if (s[i]==' '){                         //当判断出数组中出现空格，开始执行以下条件
			space_count++;                      //空格计数自增加
            /* 以下7行，是当计数过程中一旦满足空格达到4个的情况，替换为\t，
            同时将后面字符向前移动，最后使最外面的for循环的变量i的计数位置转为替换的位置。*/
			if (space_count==tabpos(pos, tab)){
				s[i-3]='\\';
				s[i-2]='\t';
				for (j=i-1, k=i+1; s[k]!='\0'; s[j++]=s[k++]);
				s[j]='\0';
				i-=2;
				space_count=0;
                pos++;
            }
		} else if (space_count > 1){                 //当判断数组中不是空格，同时空格计数大于1的情况下开始执行以下条件
			if (space_count==tabpos(pos, tab)){                 //以下7行的原理同前一个
				s[i-3]='\\';
				s[i-2]='\t';
				for (j=i-1, k=i+1; s[k]!='\0'; s[j++]=s[k++]);
				s[j]='\0';
				i-=2;
				space_count=0;
                pos++;
			}
			else{                                //此条件为空格计数不是4的情况下的处理
				for (j=i-space_count+1, k=i; s[k]!='\0'; s[j++]=s[k++]);
				s[j]='\0';
				i-=3;
				space_count=0;
			}
		}
		else                                     //当以上条件都不满足，意味着空格为1，不需要移动，空格计数归零
			space_count=0;
	}
	s[i]='\0';
}


/* tabpos：判断该次序下的转化tab需要的空格数 */
int tabpos(int pos, int* tab)
{
    if(pos > MAXLINE)            //如果pos大于MAXLINE，则返回YES，表示终止
        return 0;
    else
        return tab[pos];
}
