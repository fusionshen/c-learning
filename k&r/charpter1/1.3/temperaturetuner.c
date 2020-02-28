#include <stdio.h>

int main()
{
    float fahr;
    printf("摄氏\t华氏\n");
    for (fahr = 0; fahr <= 300; fahr = fahr +30)
        printf("%3.0f\t%6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32.0));
}