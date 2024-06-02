#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <bits/pthreadtypes.h>

typedef struct
{
	int flag;
	char sym;
} ThreadArgs;

pthread_spinlock_t spinlock;
int count = 10;

void *proc_1(void *arg)
{
	printf("\n Поток 1 начала работу\n");
	ThreadArgs *args = (ThreadArgs *)arg;

	struct timespec tp;
	tp.tv_sec = 1;
	tp.tv_nsec = 0;

	while (args->flag != 1)
	{
		while (pthread_spin_trylock(&spinlock) != 0)
		{
			sleep(1);
		}

		for (size_t i = 0; i < count; i++)
		{
			printf("%c", args->sym);
			sleep(1);
		}
		pthread_spin_unlock(&spinlock);
		nanosleep(&tp, NULL);
	}

	printf("\n Поток 1 закончил работу\n");

	// Код завершения для pthread_exit
	int exit_code = 1;
	pthread_exit((void *)&exit_code);
}

void *proc_2(void *arg)
{
	printf("\n Поток 2 начала работу\n");
	ThreadArgs *args = (ThreadArgs *)arg;

	struct timespec tp;
	tp.tv_sec = 1;
	tp.tv_nsec = 0;

	while (args->flag != 2)
	{
		while (pthread_spin_trylock(&spinlock) != 0)
		{
			sleep(1);
		}

		for (size_t i = 0; i < count; i++)
		{
			printf("%c", args->sym);
			sleep(1);
		}
		pthread_spin_unlock(&spinlock);
		nanosleep(&tp, NULL);
	}

	printf("\n Поток 2 закончил работу\n");

	int exit_code = 2;
	pthread_exit((void *)&exit_code);
}

void sig_handler(int signo)
{
	printf("\n\nget SIGINT; %d\n", signo);
	pthread_spin_destroy(&spinlock);
	exit(0);
}

int main()
{
	printf(" Программа начала работу\n");

	signal(SIGINT, sig_handler);

	int pth_create;
	int pth_join;

	pthread_spin_init(&spinlock, 0);
	pthread_t id_1, id_2;
	ThreadArgs args_1, args_2;

	args_1.flag = 0;
	args_1.sym = '1';
	args_2.flag = 0;
	args_2.sym = '2';

	pth_create = pthread_create(&id_1, NULL, proc_1, &args_1);
	if (pth_create != 0)
		printf("Func error while create th1: %s\n", strerror(pth_create));

	pth_create = pthread_create(&id_2, NULL, proc_2, &args_2);
	if (pth_create != 0)
		printf("Func error while create th2: %s\n", strerror(pth_create));

	printf("\n Программа ждёт нажатия клавиши\n");
	getchar();
	printf("\n Клавиша нажата\n");

	args_1.flag = 1;
	args_2.flag = 2;

	// Переменные для кодов завершения
	int exit_code_1, exit_code_2;

	pth_join = pthread_join(id_1, (void **)&exit_code_1);
	if (pth_join != 0)
		printf("Func error while join th 1: %s\n", strerror(pth_join));

	pth_join = pthread_join(id_2, (void **)&exit_code_2);
	if (pth_join != 0)
		printf("Func error while join th 2: %s\n", strerror(pth_join));

	pthread_spin_destroy(&spinlock);

	printf("\n\n Программа закончила работу");

	return 0;
}
