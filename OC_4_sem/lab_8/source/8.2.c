// 8_server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int flag_wait_conn = 0;
int flag_get = 0;
int flag_send = 0;
int listen_socket;
int interaction_socket;
pthread_mutex_t mut;
pthread_cond_t cond;
char *request = NULL;

void sig_handler(int signo)
{
    printf("Клиент больше не активен\n");
}

void *server_get(void *arg)
{
    while (flag_get == 0)
    {
        char rcvbuff[BUFFER_SIZE];
        int reccount = recv(interaction_socket, rcvbuff, BUFFER_SIZE, 0);
        if (reccount == -1)
        {
            perror("Ошибка при получении данных");
            sleep(1);
        }
        else if (reccount == 0)
        {
            shutdown(interaction_socket, SHUT_RDWR);
            sleep(1);
        }
        else
        {
            pthread_mutex_lock(&mut);
            request = strdup(rcvbuff);
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mut);
            printf("Получено: %s\n", rcvbuff);
        }
    }
    return NULL;
}

void *server_send(void *arg)
{
    while (flag_send == 0)
    {
        char response[BUFFER_SIZE];
        pthread_mutex_lock(&mut);
        while (request == NULL)
        {
            pthread_cond_wait(&cond, &mut);
        }
        printf("Обработка запроса: %s\n", request);

        int fd_size = getdtablesize();
        snprintf(response, sizeof(response), "Запрос: %s Ответ: %d", request, fd_size);
        free(request);
        request = NULL;
        pthread_mutex_unlock(&mut);

        int send_result = send(interaction_socket, response, BUFFER_SIZE, 0);
        if (send_result == -1)
        {
            perror("Ошибка при отправке данных");
        }
        else
        {
            printf("Ответ отправлен: %s\n", response);
        }
        sleep(1);
    }
    return NULL;
}

void *server_connection(void *arg)
{
    printf("Сервер ожидает соединения\n");

    while (flag_wait_conn == 0)
    {
        struct sockaddr_in clientAddr;
        socklen_t len = sizeof(clientAddr);
        interaction_socket = accept(listen_socket, (struct sockaddr *)&clientAddr, &len);

        if (interaction_socket == -1)
        {
            perror("Ошибка соединения");
            sleep(1);
        }
        else
        {
            printf("Адрес сокета клиента: %s\n", inet_ntoa(clientAddr.sin_addr));
            fcntl(interaction_socket, F_SETFL, O_NONBLOCK);
            pthread_t send_thread, get_thread;

            if (pthread_create(&send_thread, NULL, server_send, NULL) != 0)
            {
                perror("Ошибка при создании потока отправки");
                continue;
            }
            if (pthread_create(&get_thread, NULL, server_get, NULL) != 0)
            {
                perror("Ошибка при создании потока получения");
                pthread_cancel(send_thread);
                continue;
            }

            pthread_join(send_thread, NULL);
            pthread_join(get_thread, NULL);
        }

        shutdown(interaction_socket, SHUT_RDWR);
        close(interaction_socket);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    signal(SIGPIPE, sig_handler);
    pthread_t wait_conn;
    pthread_mutex_init(&mut, NULL);
    pthread_cond_init(&cond, NULL);

    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket == -1)
    {
        perror("Ошибка создания слушающего сокета");
        exit(EXIT_FAILURE);
    }

    fcntl(listen_socket, F_SETFL, O_NONBLOCK);
    printf("Слушающий сокет успешно создан\n");

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(listen_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Ошибка привязки");
        close(listen_socket);
        exit(EXIT_FAILURE);
    }

    int optval = 1;
    setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    if (listen(listen_socket, 1) == -1)
    {
        perror("Ошибка при прослушивании");
        close(listen_socket);
        exit(EXIT_FAILURE);
    }

    printf("Сокет начал прослушивание\n");

    if (pthread_create(&wait_conn, NULL, server_connection, NULL) != 0)
    {
        perror("Ошибка при создании потока соединения");
        close(listen_socket);
        exit(EXIT_FAILURE);
    }

    getchar();
    flag_wait_conn = 1;
    flag_get = 1;
    flag_send = 1;

    pthread_join(wait_conn, NULL);

    printf("Работа сервера завершена\n");
    pthread_mutex_destroy(&mut);
    pthread_cond_destroy(&cond);
    close(listen_socket);
    return 0;
}

int getdtablesize(void)
{
    struct rlimit rlp;
    if (getrlimit(RLIMIT_NOFILE, &rlp) == 0)
    {
        return (int)rlp.rlim_cur;
    }
    else
    {
        perror("Ошибка получения размера таблицы дескрипторов");
        return -1;
    }
}
