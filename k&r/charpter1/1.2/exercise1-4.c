#include <stdio.h>

int main()
{
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    celsius = lower;
    printf("摄氏\t华氏\n");
    while (celsius <= upper) {
        //celsius = (5.0/9.0) * (fahr - 32.0) ;
        fahr = (9.0/5.0) * celsius + 32.0 ;
        printf("%3.0f\t%6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}