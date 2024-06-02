#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int flag;
    char sym;
} ThreadArgs;

void *proc_1(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    printf("Поток 1 начала работу\n");
    
    while (args->flag != 1) {
        printf("%c\n", args->sym);
        sleep(1);
    }

    printf("Поток 1 закончил работу\n");

    // Код завершения для pthread_exit
    int exit_code = 1;
    pthread_exit((void *)&exit_code);
}

void *proc_2(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    printf("Поток 2 начала работу\n");

    while (args->flag != 2) {
        printf("%c\n", args->sym);
        sleep(1);
    }

    printf("Поток 2 закончил работу\n");

    int exit_code = 2;
    pthread_exit((void *)&exit_code);
}

int main() {
    printf("Программа начала работу\n");

    pthread_t id_1, id_2;
    ThreadArgs args_1, args_2;
    
    args_1.flag = 0;
    args_1.sym = '1';
    args_2.flag = 0;
    args_2.sym = '2';

    pthread_create(&id_1, NULL, proc_1, &args_1);
    pthread_create(&id_2, NULL, proc_2, &args_2);

    printf("Программа ждёт нажатия\n");
    getchar();
    printf("Клавиша нажата\n");

    args_1.flag = 1;
    args_2.flag = 2;

    // Переменные для кодов завершения
    int exit_code_1, exit_code_2;

    pthread_join(id_1, (void **)&exit_code_1);
    pthread_join(id_2, (void **)&exit_code_2);

    printf("Поток 1 завершился с кодом: %d\n", exit_code_1);
    printf("Поток 2 завершился с кодом: %d\n", exit_code_2);

    printf("Программа закончила работу\n");

    return 0;
}
