#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

/* 编写一个程序以确定分别由signed及unsigned限定的char、short、int与long类型变量的取值范围。
* 采用打印标准头文件中的相应值以及直接计算两种方式实现。后一种方法的实现较困难一些，因为要确定
* 各种浮点型的取值范围 */
int main()
{
    printf("采用打印标准头文件limits.h中的相应值：\n");
    //signed types
    printf("signed char min = %d\n", SCHAR_MIN);
    printf("signed char max = %d\n", SCHAR_MAX);
    printf("signed short min = %d\n", SHRT_MIN);
    printf("signed short max = %d\n", SHRT_MAX);
    printf("signed int min = %d\n", INT_MIN);
    printf("signed int max = %d\n", INT_MAX);
    printf("signed long min = %ld\n", LONG_MIN);
    printf("signed long max = %ld\n", LONG_MAX);
    //unsigned types
    printf("unsigned char max = %u\n", UCHAR_MAX);
    printf("unsigned short max = %u\n", USHRT_MAX);
    printf("unsigned int max = %u\n", UINT_MAX);
    printf("unsigned long max = %lu\n", ULONG_MAX);
    system("pause");
    return 0;
}
