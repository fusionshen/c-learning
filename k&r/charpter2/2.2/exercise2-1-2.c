#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

/* 编写一个程序以确定分别由signed及unsigned限定的char、short、int与long类型变量的取值范围。
* 采用打印标准头文件中的相应值以及直接计算两种方式实现。后一种方法的实现较困难一些，因为要确定
* 各种浮点型的取值范围 */
int main()
{
    int j;                                       //定义一个对比变量
	signed char sc_i;
	for (sc_i=1, j=0; sc_i==j+1; sc_i++, j++);
	printf("signed char max=%d, ", j);
	for (sc_i=-1, j=0; sc_i==j-1; sc_i--, j--);
	printf("signed char min=%d\n", j);
	unsigned char uc_i;
	for (uc_i=1, j=0; uc_i==j+1; uc_i++, j++);
	printf("unsigned char max=%u\n", j);         //需要注意无符号输出的格式为%u
	signed short ss_i;
	for (ss_i=1, j=0; ss_i==j+1; ss_i++, j++);
	printf("signed short max=%d, ", j);
	for (ss_i=-1, j=0; ss_i==j-1; ss_i--, j--);
	printf("signed short min=%d\n", j);
	unsigned short us_i;
	for (us_i=1, j=0; us_i==j+1; us_i++, j++);
	printf("unsigned short max=%u\n", j);        //需要注意无符号输出的格式为%u
	/*需要注意int和long的情况下，无符号的正数值范围要超过有符号的，所以，在定义无符号的变量时，
	要重新定义一个无符号对比变量*/
	signed int si_i;
	for (si_i=1, j=0; si_i>j; si_i++, j++);
	printf("signed int max=%d, ", j);
	for (si_i=-1, j=0; si_i<j; si_i--, j--);
	printf("signed int min=%d\n", j);
	unsigned int ui_i, k;
	for (ui_i=1, k=0; ui_i>k; ui_i++, k++);
	printf("unsigned int max=%u\n", k);          //需要注意无符号输出的格式为%u
	signed long sl_i;
	for (sl_i=1, j=0; sl_i>j; sl_i++, j++);
	printf("signed long max=%d, ", j);
	for (sl_i=-1, j=0; sl_i<j; sl_i--, j--);
	printf("signed long min=%d\n", j);
	unsigned long ul_i, m;
	for (ul_i=1, m=0; ul_i>m; ul_i++, m++);
	printf("unsigned long max=%u\n", m);         //需要注意无符号输出的格式为%u
	system("pause");
	return 0;
}
