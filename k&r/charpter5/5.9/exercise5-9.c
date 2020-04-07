#include <stdio.h>

int dayofyear(int year, int month, int day);
void monthday(int year, int yearday, int *month, int *day);

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/*
** 用指针方式代替数组下标方式改写函数day_of_year和month_day
*/
int main(){
    int x;
    int a, b, c;
    int month, day;
    printf("type your command:\nget day of year type 1\nchange day to date type 2\n");
    scanf("%d", &x);
    switch (x) {
    case 1:
        printf("type year-month-day(like 2019-12-23):\n");
        scanf("%d-%d-%d", &a, &b, &c);
        x = dayofyear(a, b, c);
        printf("this is %dth day of the year.\n", x);
        break;
    case 2:
        printf("type year-day(like 2019-80):\n");
        scanf("%d-%d", &a, &b);
        monthday(a, b, &month, &day);
        printf("thie date is %d-%d-%d\n", a, month, day);
        break;
    default:
        printf("wrong input!\n");
        break;
    }
    return 0;
}

int dayofyear(int year, int month, int day){
    int flag;
    char *p;
    flag = (year%4 == 0 && year%100 != 0) || year%400 == 0;
    if(month < 1 || month > 12)
        return -1;
    if(day < 1 || day > daytab[flag][month])
        return -1;
    p = daytab[flag];
    while(--month)
        day += *++p;
    return day;
}

void monthday(int year, int yearday, int *month, int *day){
    int flag;
    int i = 1;
    char *p;
    int w;
    flag= (year%4 == 0 && year%100 != 0) || year%400 == 0;
    w = (flag == 1) ? 366 : 365;
    if(yearday < 1 || yearday > w){
        *month = -1;
        *day = -1;
        return ;
    }
    p = daytab[flag];
    while(yearday > *++p){
        yearday -= *p;
        i++;
    }
    *month = i;
    *day = yearday;
}
