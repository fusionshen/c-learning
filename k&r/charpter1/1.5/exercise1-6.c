#include <stdio.h>
#include <stdlib.h>

int main()
{
	/*windows Ctrl+Z,mac Ctrl+D*/
    printf("%d\n", getchar()!=EOF);
	system("pause");
	return 0;
}