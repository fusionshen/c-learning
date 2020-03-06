#include <stdio.h>
#include <limits.h>
#include <string.h>

void itoa(int n, char s[]);
void reverse(char s[]);
void itoa_n(int n, char s[]);

/*
** 在数的对二的补码表示中，我们编写的itoa函数不能处理最大的复数，即n等于-2的(字长-1)次方的情况。请解释其原因。
** 修改该函数，使它在任何机器上运行时都能打印出正确的值。
*/
int main()
{
    int n = INT_MIN;
    char s[100];
    itoa_n(n, s);
    printf("min int after new itoa %s\n", s);
    itoa(n, s);
    printf("min int after old itoa %s\n", s);
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
/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0) /* record sign */
        n = -n; /* make n positive */
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int c, i, j;
    for(i = 0, j = strlen(s) - 1; i < j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


void itoa_n(int n, char s[])
{
    int i = 0;
    int sign = n;
    unsigned n_copy;
    if ((sign = n) < 0) {
        if((n-1) > 0)
            n_copy = n;
        else
            n_copy = -n;
    } else
        n_copy = n;
    do {
        s[i++] = n_copy % 10 + '0';
    } while ((n_copy /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}
