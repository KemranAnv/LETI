#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define SHM_ITER_N "/mySharedIteration"

#define SHM_NAME "/mySharedMemory"
#define SHM_WRITE_N "/my_sem_write"
#define SHM_READ_N "/my_sem_read"

int fin_flag = 0;

sem_t *sem_write = NULL;
sem_t *sem_read = NULL;

int shm_fd = -1;
int shm_iter_fd = -1;

int *local_addr = NULL;
int *iteration = NULL; // добавляем переменную итерации

void cleanup()
{
	if (local_addr)
		munmap(local_addr, getdtablesize());

	if (iteration)
		munmap(iteration, sizeof(int));

	if (sem_write)
	{
		sem_close(sem_write);
		sem_unlink(SHM_WRITE_N);
	}

	if (sem_read)
	{
		sem_close(sem_read);
		sem_unlink(SHM_READ_N);
	}

	if (shm_fd != -1)
		shm_unlink(SHM_NAME);

	if (shm_iter_fd != -1)
		shm_unlink(SHM_ITER_N);
}

void sig_handler(int signo)
{
	cleanup();
	printf("\n\nget SIGINT; %d\n", signo);
	exit(0);
}

void *th_func(void *arg)
{
	printf("\n Началась поточная функция 6.1 \n");

	(*iteration)++;

	while (!fin_flag)
	{
		int result = getdtablesize();
		printf("Iteration: %d, Result: %d\n", *iteration, result); // выводим значение итерации
		memcpy(local_addr, &result, sizeof(result));
		sem_post(sem_write);
		sem_wait(sem_read);
		sleep(1);
		(*iteration)++; // увеличиваем значение итерации
	}
	printf("\n Закончилась поточная функция 6.1 \n");

	int exit_code = 1;
	pthread_exit((void *)&exit_code);
	// return NULL;
}

int main()
{
	printf(" Программа 6.1 начала работу\n");

	pthread_t th;
	if (signal(SIGINT, sig_handler) == SIG_ERR) {
        perror("Ошибка при установке обработчика сигнала 6.1");
        return 1;
    }

	shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0644);
	ftruncate(shm_fd, getdtablesize());
	local_addr = mmap(0, getdtablesize(), PROT_WRITE, MAP_SHARED, shm_fd, 0);

	shm_iter_fd = shm_open(SHM_ITER_N, O_CREAT | O_RDWR, 0644);
    ftruncate(shm_iter_fd, sizeof(int));
	iteration = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_iter_fd, 0); 
	// отображаем переменную итерации в разделяемую память

	sem_write = sem_open(SHM_WRITE_N, O_CREAT, 0644, 0);
	if (sem_write == SEM_FAILED) {
        perror("Ошибка при открытии семафора sem_write 6.1");
        return 1;
    }
	sem_read = sem_open(SHM_READ_N, O_CREAT, 0644, 0);
	if (sem_read == SEM_FAILED) {
        perror("Ошибка при открытии семафора sem_read 6.1");
        return 1;
    }

	int pth_create = pthread_create(&th, NULL, th_func, NULL);
	if (pth_create != 0)
		printf("Func error while create thread in 6.1: %s\n", strerror(pth_create));

	printf("\n Программа ждёт нажатия клавиши\n");
	getchar();
	printf("\n Клавиша нажата\n");
	
	fin_flag = 1;

	int exit_code;
	int	pth_join = pthread_join(th, (void **)&exit_code);
	if (pth_join != 0)
		printf("Func error while join thread in 6.1: %s\n", strerror(pth_join));

	cleanup();

	printf("\n\n Программа 6.1 закончила работу");

	return 0;
}
