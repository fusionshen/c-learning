#include <stdio.h>

#define swap(t, x, y) {t temp; temp = x; x = y; y = temp;}

int main()
{
    int a = 1;
    int b = 2;
    printf("a=%d,b=%d\n", a, b);
    swap(int, a, b);
    printf("a=%d,b=%d\n", a, b);

}
