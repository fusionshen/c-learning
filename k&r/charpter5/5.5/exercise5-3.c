#include <stdio.h>
#include <string.h>
#define MAXLEN 100

int getline(char *s);
void strcat(char *s, char *t);

/* 用指针方式实现第二章中的函数strcat。函数strcat（s，t)将t指向的字符串复制到s指向的字符串尾部。 */
int main()
{
    char s[MAXLEN], t[MAXLEN];
    printf("type string s:");
    getline(s);
    printf("type string t:");
    getline(t);
    strcat(s, t);
    printf("the new string s:%s", s);
}

int getline (char *s)
{
    int c;
    while((c = getchar()) != EOF && c != '\n')
        *s++ = c;
    *s = '\0';
    return strlen(s);
}

/* strcat: concatenate t to end of s; s must be big enough */
void strcat(char *s, char *t)
{
    while(*s != '\0')
        s++;
    while((*s++ = *t++))
        ;
}
