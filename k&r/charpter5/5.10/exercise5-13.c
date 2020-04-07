#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define TAILLENGTH 10 /* 默认尾部长度 */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writetaillines(char *lineptr[], int nlines, int tail);

/*
* 编写程序tail，将其输入中的最后n行打印出来。默认情况下，n的值为10，但可通过
* 一个可选参数改变n的值，因此，命名
* tail -n
* 将打印其输入的最后n行。无论输入与n的值是否合理，该程序都应该能正常运行。编
* 写的程序要充分地利用存储空间：输入行的存储方式应该同5.6节中排序程序的存储方
* 式一样，而不是蚕蛹固定长度的二维数组
*/
int main(int argc, char* argv[])
{
    int c, nlines, taillen = 0; /* number of input lines read */
    while(--argc > 0 && (c = **++argv) == '-')
            switch (c){
            case '-':
                taillen = atoi(*argv+1);
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                break;
            }
    taillen = taillen == 0 ? TAILLENGTH : taillen;
    printf("tail length: %d\n", taillen);

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        writetaillines(lineptr, nlines, taillen);
        return 0;
    } else {
        printf("error: input too big to print tail\n");
        return 1;
    }
}

#define MAXLEN 1000 /* max length of any input line */
int getline(char *, int);
char *alloc(int);
void afree(char *p);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len+1)) == NULL)
            return -1;
        else {
            line[len] = '\0';  /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* writetaillines: write output tail lines */
void writetaillines(char *lineptr[], int nlines, int tail)
{
    for (int i = nlines - tail; i < nlines ; i++)
        if (*(*lineptr+i) != '\0')  // 复数指针内容为空
            printf("%s\n", *(lineptr+i));
}

/* getline: */
int getline(char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return i;
}


#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

char *alloc(int n) /* return pointer to n characters */
{
    if(allocbuf + ALLOCSIZE - allocp >= 0) { /* it fits */
        allocp += n;
        return allocp - n; /* old p */
    } else          /* not enough room */
        return 0;
}

void afree(char *p) /* free storage pointed to by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
