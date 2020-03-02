// 版权声明：本文为CSDN博主「taolusi」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/taolusi/article/details/52400918
#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

/*
** 编写一个函数setbits(x, p ,n, y)，该函数返回对x执行下列操作后的结果值:
** 将x中从第p位开始的n个(二进制)位设置为y中最右边n位的值，x的其余各位保持不变。
*/
int main()
{
    unsigned int x = 73;
    unsigned int y = 23;
    int p = 5;
    int n = 3;
    int r;
    r = setbits(x, p, n, y);
    printf("%d", r); //r的结果应为121
    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    return (x & ~(~(~0 << n) << (p+1-n))) | (y & ~(~0 << n)) << (p+1-n);
}
