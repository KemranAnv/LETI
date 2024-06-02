#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	printf("\nПрограмма(родительская) 1 начала работу\n\n");

	printf("ID родительского процесса: %d\n", getppid());
	printf("ID процесса: %d\n\n", getpid());

	// что хранится в argv
	for (int i = 0; i < argc; i++)
		printf("%s\n", argv[i]);

	pid_t pid = fork();

	printf("\nЗаходим в условия после fork в родительском процессе\n");

	if (pid == 0){
		char *argv[] = {"./4.1", "arg1", "arg2", "arg3", "arg4", NULL};
		execv("./4.1", argv);
		perror("execv failed");
        exit(EXIT_FAILURE);
	}
	else if (pid == -1){
		perror("fork error ");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0){
		printf("ID дочернего процесса: %d\n", pid);
		int status;
		while(waitpid(pid, &status, WNOHANG) == 0){
			printf("Ждём...\n");
			sleep(1);
		}
		printf("Код завершения дочернего процесса: %d\n", WEXITSTATUS(status));
	}
	printf("\nВышел из условия в родительском процессе\n");

	printf("\nПрограмма(родительская) 1 закончила работу\n");

	return 0;
}
