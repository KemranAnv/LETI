#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

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

	while (args->flag != 1)
	{
		pthread_spin_lock(&spinlock);
		for (size_t i = 0; i < count; i++)
		{
			printf("%c", args->sym);
			sleep(1);
		}
		pthread_spin_unlock(&spinlock);
		sleep(1);
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

	while (args->flag != 2)
	{
		pthread_spin_lock(&spinlock);
		for (size_t i = 0; i < count; i++)
		{
			printf("%c", args->sym);
			sleep(1);
		}
		pthread_spin_unlock(&spinlock);
		sleep(1);
	}

	printf("\n Поток 2 закончил работу\n");

	int exit_code = 2;
	pthread_exit((void *)&exit_code);
}

int main()
{
	printf(" Программа начала работу\n");
	int pth_create_1, pth_create_2;
	int pth_join_1, pth_join_2;

	pthread_spin_init(&spinlock, 0);
	pthread_t id_1, id_2;
	ThreadArgs args_1, args_2;

	args_1.flag = 0;
	args_1.sym = '1';
	args_2.flag = 0;
	args_2.sym = '2';

	pth_create_1 = pthread_create(&id_1, NULL, proc_1, &args_1);
	if (pth_create_1 != 0)
		printf("Func error while create th1: %s\n", strerror(pth_create_1));

	pth_create_2 = pthread_create(&id_2, NULL, proc_2, &args_2);
	if (pth_create_2 != 0)
		printf("Func error while create th2: %s\n", strerror(pth_create_2));

	printf("\n Программа ждёт нажатия клавиши\n");
	getchar();
	printf("\n Клавиша нажата\n");

	args_1.flag = 1;
	args_2.flag = 2;

	// Переменные для кодов завершения
	int exit_code_1, exit_code_2;

	pth_join_1 = pthread_join(id_1, (void **)&exit_code_1);
	if (pth_join_1 != 0)
		printf("Func error while join th 1: %s\n", strerror(pth_join_1));

	pth_join_2 = pthread_join(id_2, (void **)&exit_code_2);
	if (pth_join_2 != 0)
		printf("Func error while join th 2: %s\n", strerror(pth_join_2));

	pthread_spin_destroy(&spinlock);

	printf("\n\n Программа закончила работу");

	return 0;
}
