#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

/*
** 编写一个函数invert(x, p ,n)，该函数返回对x执行下列操作后的结果值:
** 将x中从p位开始时的n个（二进制）位求反（即，1变成0，0变成1），x的其余
** 各位保持不变
*/
int main()
{
    unsigned int x = 73;
    int p = 5;
    int n = 3;
    int r;
    r = invert(x, p, n);
    printf("%d", r); //r的结果应为121
    return 0;
}

unsigned invert(unsigned x, int p, int n)
{
    return (x & ~(~(~0 << n) << (p+1-n))) | ( ~x >> (p+1-n) & ~(~0 << n)) << (p+1-n);
}
