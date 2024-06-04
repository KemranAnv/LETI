#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <errno.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

int fin_flag = 0;

typedef struct
{
    long mtype;
    char buff[256];
} TMessage;

void *thFunc(void *arg)
{

    printf("\n Началась поточная функция 7.2 \n");

    int msgid = *(int *)arg;
    TMessage message;
    message.mtype = 1;

    while (!fin_flag)
    {
        memset(message.buff, 0, sizeof message.buff);
        int result = msgrcv(msgid, &message, sizeof(message.buff), message.mtype, IPC_NOWAIT);
        if (result < 0)
        {
            perror("msgrcv");
            // Не прерываем выполнение, а просто ждем некоторое время
            sleep(1);
            continue;
        }
        printf("Received message: %s\n", message.buff);
    }

    printf("\n Закончилась поточная функция 7.2 \n");

    return NULL;
}

int main()
{

    printf(" Программа 7.2 начала работу\n");

    key_t key = ftok("lab7", 'A');
    pthread_t th;

    int msgid = msgget(key, 0);
    if (msgid < 0)
    {
        perror("func error msgget: ");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&th, NULL, thFunc, &msgid) != 0)
    {
        perror("func error while creating th in 7.2: ");
        exit(EXIT_FAILURE);
    }

    printf("\n Программа ждёт нажатия клавиши\n");
    getchar();
    fin_flag = 1;
    printf("\n Клавиша нажата\n");

    if (msgctl(msgid, IPC_RMID, NULL) < 0)
    {
        perror("Func error: msgctl");
        exit(EXIT_FAILURE);
    }

    printf("\n\n Программа 7.2 закончила работу");

    return 0;
}
