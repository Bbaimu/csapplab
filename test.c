#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

/**
	所有的转换在函数内部进行
	对外保持统一接口
*/
void qsort1(void *, int , int , int (*comp)( const void *, const void *));
int numcmp(const void *, const void *);
int mstrcmp(const void * ,const void *);

int main (int argc, char *argv[])
{
    int nlines;
    int numeric = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort1(lineptr, 0, nlines-1,(numeric ? numcmp : mstrcmp));
        writelines(lineptr, nlines);
		getchar();
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

void qsort1(void *vv, int left, int right, int (*comp)(const void *, const void *))
{
	void **v = (void **)vv;
    int i, last;
    void swap(void *v, int, int);

    if (left >= right)
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort1(v, left, last-1, comp);
    qsort1(v, last+1, right, comp);
}

#include <stdlib.h>
int mstrcmp(const void *ss1, const void *ss2)
{
	char *s1 = (char*)ss1;
	char *s2 = (char*)ss2;

	return strcmp(s1, s2);
}
int numcmp(const void  *ss1, const void *ss2)
{
	char *s1 = (char*)ss1;
	char *s2 = (char*)ss2;
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *vv, int i, int j)
{
	void **v = (void**)vv;
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define MAXLEN 1000
int getline_(char *s, int lim);
char *alloc(int n);
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = getline_(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

int getline_(char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c=getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

#define ALLOCSIZE 10000
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else {
        return 0;
    }
}
void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}
