#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXLINES 5000 /* max #lines to be sorted */

#define ALLOCSIZE 10000 /* size of available space */


char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
int readlines_n(char *lineptr[], int nlines, char *target);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

/*
** 重写函数readlines，将输入的文本行储存到由main函数提供的一个数组中，而不是存储到调用
** 而不是存储到调用alloc分配的存储空间中。该函数的运行速度比改写前快多少？
*/
/* sort intput lines */
int main()
{
    int nlines; /* number of input lines read */
    char target[MAXLINES];
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
    }
    if ((nlines = readlines_n(lineptr, MAXLINES, target)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
    }
    return 0;
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
    clock_t time_taken = clock();
    nlines = 0;
    while((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len+1)) == NULL)
            return -1;
        else {
            line[len] = '\0';  /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    time_taken = clock() - time_taken;
    printf("readlines() took %lu clocks (%g seconds)\n",
           (unsigned long) time_taken,
           (double) time_taken / CLOCKS_PER_SEC);
    return nlines;
}

int readlines_n(char *lineptr[], int maxlines, char *target)
{
    int len, nlines;
    char *p = target;
    char line[MAXLEN];
    char *linetop = p + ALLOCSIZE;
    clock_t time_taken = clock();
    nlines = 0;
    while((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || p + len + 1 > linetop )
            return -1;
        else {
            line[len] = '\0';  /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len + 1;
        }
    time_taken = clock() - time_taken;
    printf("readlines_n() took %lu clocks (%g seconds)\n",
           (unsigned long) time_taken,
           (double) time_taken / CLOCKS_PER_SEC);
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *(lineptr++));
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

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right) /* do nothing if array contains */
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, right);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}



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
