#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <errno.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int fin_flag = 0;

typedef struct
{
    long mtype;
    char buff[256];
} TMessage;

void *thFunc(void *arg)
{

    printf("\n Началась поточная функция 7.1 \n");

    int msgid = *(int *)arg;
    TMessage message;
    message.mtype = 1;

    while (!fin_flag)
    {
        int g_t_s = getdtablesize();

        int len = sprintf(message.buff, "Table size: %d", g_t_s);

        int result = msgsnd(msgid, &message, len, IPC_NOWAIT);

        if (result < 0)
        {
            perror("msgsnd 7.1 thFunc 'while(1)' problem 4: ");
            // Не прерываем выполнение, а просто ждем некоторое время
            sleep(1);
            continue;
        }
        sleep(1);
    }

    printf("\n Закончилась поточная функция 7.1 \n");

    return NULL;
}

int main()
{
    printf(" Программа 7.1 начала работу\n");

    pthread_t th;
    key_t key = ftok("lab7", 'A');

    int msgid = msgget(key, 0644 | IPC_CREAT);
    if (msgid < 0)
    {
        perror("Func error msgget 7.1 main problem 1:");
        exit(EXIT_FAILURE);
    }

    struct msqid_ds msq;
    msgctl(msgid, IPC_STAT, &msq);
    msq.msg_qbytes = 24576; // попытка установить размер очереди больше 16384
    if (msgctl(msgid, IPC_SET, &msq) == -1)
    {
        perror("msgctl 7.1 main problem 2");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&th, NULL, thFunc, &msgid) != 0)
    {
        perror("Func error while creating th 7.1 main problem 3: ");
        exit(EXIT_FAILURE);
    }

    printf("\n Программа ждёт нажатия клавиши\n");
    getchar();
    fin_flag = 1;
    printf("\n Клавиша нажата\n");

    if (pthread_join(th, NULL) != 0)
    {
        perror("Func error while joining th 7.1 main problem 5: ");
        exit(EXIT_FAILURE);
    }

    if (msgctl(msgid, IPC_RMID, NULL) < 0)
    {
        perror("Func error msgctl 7.1 main problem last");
        exit(EXIT_FAILURE);
    }

    printf("\n\n Программа 7.1 закончила работу");

    return 0;
}
