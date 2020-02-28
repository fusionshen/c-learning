/**
***************
*   2018-4-7
*   Author : 五块钱的鸡腿
*   打印输入中单词长度的直方图.垂直方向
*   2020-2-20
*   Author : Fusionshen
*   添加水平方向
*
**/

#include <stdio.h>
#include <stdlib.h>

#define Word_IN 1   /* 在单词内*/
#define Word_Out 0  /* 在单词外*/

#define MaxWordLen 15   //单词的最大长度

void vertical(int a[] ,int n);
void horizenal(int a[], int n);

/* 编写一个程序，打印输入中单词长度的直方图，水平方向的直方图比较容易绘制，垂直方向的直方图则要困难些 */
int main()
{
    int c,i,wordLength;
    int overflowWord = 0;   //单词长度超过单词的最大长度的个数
    //存放不同长度的单词个数. 单词长度为1的存放在 wordGraph[0]
    int wordGraph[MaxWordLen];

    //初始化数组
    for(i = 0; i< MaxWordLen; ++i){
        wordGraph[i] = 0;
    }

    int state = Word_Out;    //初始在单词外
    while((c = getchar()) != EOF){
        if(c ==' ' || c == '\t' || c == '\n'){
            if(state == Word_IN){    //遇到空格和制表符判断是否在单词内
                if(wordLength <= MaxWordLen){
                    wordGraph[wordLength - 1]++;
                    state = Word_Out;
                }
                else{
                    ++overflowWord;
                }
                wordLength = 0;   //清除单词的长度,为统计下一个单词做准备.
            }
        }
        else{
            state = Word_IN;
            ++wordLength;   //在单词内,单词长度+1
        }
    }
    //调用函数
    //vertical(wordGraph,MaxWordLen);
    horizenal(wordGraph,MaxWordLen);
    printf("\nThe overflow wrod num is:%d",overflowWord);
}

//打印垂直直方图
void vertical(int a[],int n){
    //1.寻找直方图最大值
    int i,j,max=0;
    for(i=0;i<n;++i){
        if(a[i]>max){
            max =a[i];
        }
    }
    //2.值为0的不打印
    //外循环打印 y轴  高度
    //内循环打印 x轴
    for(i = max;i > 0; --i){     //从值最大的开始打印
        for(j = 0;j < n; ++j){
            if(a[j] != 0){    //如果值为0,说明不存在此长度的单词,不打印
                if(a[j] >= i){
                    printf("**  ");
                }
                else{
                    printf("    ");
                }
            }
        }
        printf("\n");
    }
    //打印单词的长度
    for(j = 0;j < n; ++j){
        if(a[j] != 0){
            printf("%-4d",j + 1);
        }
    }
    printf("\n");
    //打印各个单词长度的个数
    for(j = 0;j < n; ++j){
        if(a[j] != 0){
            printf("%-4d",a[j]);
        }
    }
}

//打印水平直方图
void horizenal(int a[],int n){
    //1.数量从大到小打印
    //打印标题
    printf("Length  nums\n");
    int i,j;
    for(i = 0;i < n; ++i){     //从值最大的开始打印
        //打印单词长度
        printf("%4d", i + 1);
        //打印单词数量
        printf("%6d    ", a[i]);
        for(j = 0; j < a[i]; ++j){
            printf("*");
        }
        printf("\n");
    }
}

