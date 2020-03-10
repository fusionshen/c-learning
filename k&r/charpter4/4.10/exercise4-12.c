#include <stdio.h>
#include <limits.h>
#include <string.h>

void itoa(int n, char s[]);

/*
** 运用printd函数的设计思想编写一个递归版本的itoa函数，即通过递归调用把整数转换为字符串。
*/
int main()
{
    int n = INT_MIN;
    char s[100];
    itoa(n, s);
    printf("min int after itoa %s\n", s);
    return 0;
}

/*
** 最大的负数的二进制形式是10000...，在上面的函数itoa中，对最大负数进行n=-n运算时，只改变其符号位，我们可以看到n将会变成0，
** 这样会得到错误的结果，这种情况下，我们可以将这个最大的负数变为无符号数，即n=（unsigned）n，这个无符号数的绝对值等于原来的最大负数的绝对值。
** 为了解决这个问题，我们需要在最开始的位置对最大的负数进行识别并处理，剩下的程序部分不需要改变，直接照搬就行。
** 判别最大负数的方法有很多，利用它的特殊性质就可以了。比如，
** 一,如果是负数的话，进行减一处理，得到的差如果大于零，说明他就是最大负数；
** 二,将这个最大负数变为无符号数，然后进行左移运算，得到结果为0的话，说明这个数就是最大负数。
*/

//-2147483648
void itoa(int n, char s[])
{
    static int i = 0;
    int sign = n;
    unsigned n_copy;
    if ((sign = n) < 0) {
        if((n-1) > 0)
            n_copy = n;
        else{
            s[i++] = '-';
            n_copy = -n;
        }
    } else
        n_copy = n;

    if (n_copy/10)
        itoa(n_copy/10, s);

    s[i++] = n_copy % 10 + '0';
    s[i] = '\0';
}


