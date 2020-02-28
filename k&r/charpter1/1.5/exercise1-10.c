#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* 编写一个将输入复制到输出的程序，并将其中的制表符替换为\t，把回退符替换为\b，把反斜杠替换为\\; 1st version*/
int main()
{
    int c;
	while((c = getchar()) != EOF){
		if (c=='\t') {
            printf("\t");
        } else if(c == '\b'){
            printf("\b");
        } else if (c == '\\'){
            printf("\\");
        } else {
            putchar(c);
        }
	}
    return 0;
}