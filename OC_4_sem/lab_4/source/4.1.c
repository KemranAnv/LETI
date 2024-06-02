#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	printf("\n  --Программа(дочерняя) 2 начала работу\n");

	printf("  --ID процесса: %d\n", getpid());
	printf("  --ID родительского процесса: %d\n\n", getppid());

	printf("  --Аргументы командной строки:\n");
	for (int i = 0; i < argc; i++)
		printf("  --%s\n", argv[i]);

	printf("\n  --Программа(дочерняя) 2 закончила работу\n");

	exit(5);
}