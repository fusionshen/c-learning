#include <stdio.h>

unsigned rightrot(unsigned x, int n);
unsigned invert(unsigned x);
int length(unsigned x);

/*
** 编写一个函数rightrot(x,n)，该函数返回将x循环右移（即从最右端移出的位将从最左端移入）n（二进制）位所得到的值
*/
int main()
{
    // 10111 1+2+4+16 = 23
    // 11011
    // 11011
    // 11110 2+4+8+16 = 30
    unsigned int x = 23;
    int n = 3;
    int r;
    r = rightrot(x, n);
    printf("%d", r); //r的结果应为121
    return 0;
}

unsigned rightrot(unsigned x, int n)
{
    for (int j = 0; j < n; ++j)
        x = invert(x);
    return x;
}


unsigned invert(unsigned x)
{
    return x >> 1 | (x & 1) << length(x);
}

int length(unsigned x)
{
    int i;
    for(i = 0; (x = x >> 1) > 0; ++i)
        ;
    return i;
}
