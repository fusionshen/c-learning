#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void entab(char s[]);                         //定义函数entab
int main()
{
	char string[80];                         //定义一个足够大的数组
	printf("Please enter string: ");         //输入一个字符串
	gets(string);
	entab(string);                           //调用entab函数
	puts(string);                            //输出变换后的字符串
	system("pause");
	return 0;
}
/*entab函数*/
void entab(char s[])
{
	int i, j, k, len, space_count;              //定义变量，len是字符串长度，space_count是空格计数
	len=strlen(s);                              //测出字符串长度
	s[len]='\0';                                //给字符串加上终止符
	for (i=0, space_count=0; s[i]!='\0'; i++){
		if (s[i]==' '){                         //当判断出数组中出现空格，开始执行以下条件
			space_count++;                      //空格计数自增加
/*以下7行，是当计数过程中一旦满足空格达到4个的情况，替换为\t，
同时将后面字符向前移动，最后使最外面的for循环的变量i的计数位置转为替换的位置。*/
			if (space_count==4){
				s[i-3]='\\';
				s[i-2]='\t';
				for (j=i-1, k=i+1; s[k]!='\0'; s[j++]=s[k++]);
				s[j]='\0';
				i-=2;
				space_count=0;
			}
		}
		else if (space_count>1){                 //当判断数组中不是空格，同时空格计数大于1的情况下开始执行以下条件
			if (space_count==4){                 //以下7行的原理同前一个
				s[i-3]='\\';
				s[i-2]='\t';
				for (j=i-1, k=i+1; s[k]!='\0'; s[j++]=s[k++]);
				s[j]='\0';
				i-=2;
				space_count=0;
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