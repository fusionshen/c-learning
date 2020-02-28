/**
***************
*   2020-2-20
*   Author : Fusionshen
*   打印输入中各个字符出现频度的直方图
*
**/

#include <stdio.h>
#include <stdlib.h>

#define MaxCharacterLen 94   //字符的最大数量'!'~127

void vertical(int a[], int n, int m);
void horizenal(int a[], int n, int m);

int main()
{
    int c,i;
    int unkownCharacter = 0;   //不识别的字符个数
    //频度是百分比，故需要求值比例
    int totalnum = 0; //字符总数
    //存放不同的字符个数. ascii码为'!'(!叹号)的存放在 characterGraph[0]
    int characterGraph[MaxCharacterLen];

    //初始化数组
    for(i = 0; i< MaxCharacterLen; ++i){
        characterGraph[i] = 0;
    }
    while((c = getchar()) != EOF){
        if(c >='!' && c <= 126){
            ++characterGraph[c - '!'];
        }
        else{
             ++unkownCharacter;
        }
        ++totalnum;
    }
    //调用函数
    vertical(characterGraph, MaxCharacterLen, totalnum-unkownCharacter);
    //horizenal(characterGraph, MaxCharacterLen, totalnum-unkownCharacter);
    printf("\nThe unkown character num is:%d",unkownCharacter);
}

//打印垂直直方图
void vertical(int a[],int n, int m){
    //1.寻找直方图最大值
    int i,j,max=0;
    for(i=0;i<n;++i){
        if(a[i]*100/m > max){
            max = a[i]*100/m;
        }
    }
    //2.值为0的不打印
    //外循环打印 y轴  高度
    //内循环打印 x轴
    for(i = max; i > 0; --i){     //从值最大的开始打印
        for(j = 0;j < n; ++j){
            if(a[j] != 0){    //如果值为0,说明不存在此长度的单词,不打印
                if(a[j] >= i){
                    printf("***  ");
                }
                else{
                    printf("     ");
                }
            }
        }
        printf("\n");
    }
    //打印字符
    for(j = 0;j < n; ++j){
        if(a[j] != 0){
            //打印具体字符
            printf("%2s","");
            putchar(j + '!');
            printf("%2s","");
        }
    }
    printf("\n");
    //打印各个字符出现的次数
    for(j = 0;j < n; ++j){
        if(a[j] != 0){
            printf("%3d  ",a[j]);
        }
    }
    printf("\n");
    //打印各个字符出现的频次
    for(j = 0;j < n; ++j){
        if(a[j] != 0){
            printf("%2d%-3s",a[j]*100/m,"%");
        }
    }
}

//打印水平直方图
//m为有效字符数量
void horizenal(int a[],int n, int m){
    //1.数量从大到小打印
    //打印标题
    printf("character  nums  frequency\n");
    int i,j;
    for(i = 0; i < n; ++i){     //从值最大的开始打印
        //打印对齐空白
        printf("%6s", "");
        //打印具体字符
        putchar(i + '!');
        //打印字符数量
        printf("%6d    ", a[i]);
        //打印频度
        printf("%6d%%    ", a[i]*100/m);
        for(j = 0; j <  a[i]*100/m; ++j){
            printf("*");
        }
        printf("\n");
    }
}

