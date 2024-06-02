#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h>
#include <poll.h>

#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#define SEM_NAME "/sem_name"
#define FILE_NAME "sem.txt"

char symbol = '2';

sem_t *semaphore = SEM_FAILED;
int fd = -1;

void cleanup()
{
	if (fd != -1)
	{
		close(fd);
	}
	if (semaphore != SEM_FAILED)
	{
		sem_close(semaphore);
		sem_unlink(SEM_NAME);
	}
}

void sig_handler(int signo)
{
	cleanup();
	printf("\n\nget SIGINT; %d\n", signo);
	exit(0);
}

int main(int argc, char const *argv[])
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
	{
		perror("Ошибка при установке обработчика сигнала");
		return 1;
	}

	semaphore = sem_open(SEM_NAME, O_CREAT, 0644, 1);
	if (semaphore == SEM_FAILED)
	{
		perror("Ошибка при открытии семафора");
		return 1;
	}

	fd = open(FILE_NAME, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Ошибка при открытии файла");
		cleanup();
		return 1;
	}

	struct pollfd fds[1];
	int time_msecs = 1000;
	int ret = 0;

	fds[0].fd = 0;
	fds[0].events = POLLIN;

	while (1)
	{
		if (sem_wait(semaphore) == -1)
		{
			perror("Ошибка при ожидании семафора");
			cleanup();
			return 1;
		}

		for (int i = 0; i < 3; i++)
		{
			if (write(fd, &symbol, 1) == -1)
			{
				perror("Ошибка при записи в файл");
				cleanup();
				return 1;
			}
			printf("%c", symbol);
			sleep(1);
		}

		printf("\n\n");

		if (sem_post(semaphore) == -1)
		{
			perror("Ошибка при освобождении семафора");
			cleanup();
			return 1;
		}

		sleep(1);

		ret = poll(fds, 1, time_msecs);

		if (ret > 0)
		{
			printf("Клавиша enter была нажата.\n");
			break;
		}
		else if (ret == 0)
			printf("Клавиша enter не была нажата.\n");
		else
		{
			perror("Ошибка при вызове poll");
			cleanup();
			return 1;
		}
	}

	cleanup();

	return 0;
}
