#include <stdio.h>

int bitcount(unsigned x);
/*
** 在求对二的补码时，表达式 x &= (x - 1)可以删除x中最右边值为1的
** 一个二进制位。请解释这样这样做的道理。用这一方法重写bitcount函数，以加快其执行速度。
*/

// 因为二进制的特性， 不是0 就是1， 所以x 与 x - 1的最右边值一定是互反的， 这样，x & （x - 1）的最右边的值一定为0，
// 如此循环后x的最终值为0，循环次数即为x中值为1的个数。

int main()
{
    // 10111 1+2+4+16 = 23
    // 11110 2+4+8+16 = 30
    unsigned int x = 23;
    int r;
    r = bitcount(x);
    printf("%d", r); //r的结果应为4
    return 0;
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
    int b;

    // for (b = 0; x != 0; x >>= 1 )
    //     if (x & 01)
    //         b++;

    for (b = 0; x != 0; ++ b )
        x &= (x - 1);
    return b;
}
