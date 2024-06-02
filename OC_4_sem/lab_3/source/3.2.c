#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#include <fcntl.h>

typedef struct
{
	int flag;
	char sym;
} ThreadArgs;

int pipefd[2];

void *th_write(void *arg)
{
	printf("\n Поток 1 начала работу\n");

	ThreadArgs *args = (ThreadArgs *)arg;
	char buff[256];

	int g_t_s = getdtablesize(); // - получить размер таблицы дескрипторов; передать полученное число.
	sprintf(buff, "Размер таблицы дескрипторов: %d", g_t_s); // сформировать из данных сообщение в буфере

	while (args->flag != 1)
	{
		ssize_t nw = write(pipefd[1], buff, strlen(buff) + 1);
		if (nw > 0)
			printf("Записано %zd байт в канал\n", nw);
		else if (nw == -1)
			perror("Func error: ");

		sleep(1);
	}

	printf("\n Поток 1 закончил работу\n");

	// Код завершения для pthread_exit
	int exit_code = 1;
	pthread_exit((void *)&exit_code);
}

void *th_read(void *arg)
{
	printf("\n Поток 2 начала работу\n");

	ThreadArgs *args = (ThreadArgs *)arg;
	char buff[256];

	while (args->flag != 2)
	{
		ssize_t nr = read(pipefd[0], buff, sizeof(buff));
		if (nr == 0)
			printf("End of a file\n");
		else if (nr == -1)
			perror("Func error: ");
		else if (nr > 0)
			printf("Прочитано %zd байт из канала: %s\n", nr, buff);

		sleep(1);
	}

	printf("\n Поток 2 закончил работу\n");

	int exit_code = 2;
	pthread_exit((void *)&exit_code);
}

void sig_handler(int signo)
{
	printf("\n\nget SIGINT; %d\n", signo);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(0);
}

int main(int argc, char const *argv[])
{
	printf(" Программа начала работу\n");

	pthread_t th1, th2;

	int pth_create1, pth_create2;
	int pth_join1, pth_join2;
	signal(SIGINT, sig_handler);

	ThreadArgs args_1, args_2;
	args_1.flag = 0;
	args_1.sym = '1';
	args_2.flag = 0;
	args_2.sym = '2';

	int flags = O_NONBLOCK;
	int rv = pipe2(pipefd, flags);
	if (rv == -1)
		perror("Error creating the pipe");

	pth_create1 = pthread_create(&th1, NULL, th_write, &args_1);
	if (pth_create1 != 0)
		printf("Func error while create th1: %s\n", strerror(pth_create1));

	pth_create2 = pthread_create(&th2, NULL, th_read, &args_2);
	if (pth_create2 != 0)
		printf("Func error while create th2: %s\n", strerror(pth_create2));

	printf("\n Программа ждёт нажатия клавиши\n");
	getchar();
	printf("\n Клавиша нажата\n");

	args_1.flag = 1;
	args_2.flag = 2;

	// Переменные для кодов завершения
	int exit_code_1, exit_code_2;

	pth_join1 = pthread_join(th1, (void **)&exit_code_1);
	if (pth_join1 != 0)
		printf("Func error while join th 1: %s\n", strerror(pth_join1));

	pth_join2 = pthread_join(th2, (void **)&exit_code_2);
	if (pth_join2 != 0)
		printf("Func error while join th 2: %s\n", strerror(pth_join2));

	close(pipefd[0]);
	close(pipefd[1]);

	printf("\n\n Программа закончила работу");

	return 0;
}
