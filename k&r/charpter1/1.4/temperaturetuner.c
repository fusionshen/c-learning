#include <stdio.h>
#define LOWER 0 /* lower limit of table*/
#define UPPER 300 /*upper limit*/
#define STEP 30 /* step size*/

int main()
{
    float fahr;
    printf("摄氏\t华氏\n");
    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf("%3.0f\t%6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32.0));
}