#include <stdio.h>

float teperatureturner(float fahr);

int main()
{
    float fahr;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    printf("摄氏\t华氏\n");
    while (fahr <= upper) {
        printf("%3.0f\t%6.1f\n", fahr, teperatureturner(fahr));
        fahr = fahr + step;
    }
}

float teperatureturner(float fahr)
{
    return (5.0/9.0) * (fahr - 32.0);
}