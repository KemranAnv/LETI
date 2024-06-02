// 8_client
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int flag_wait_conn = 0;
int flag_get = 0;
int flag_send = 0;
int interaction_socket;

void sig_handler(int signo)
{
    printf("Сервер больше не активен\n");
}

void *client_get(void *arg)
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
            printf("Ответ от сервера: %s\n", rcvbuff);
        }
    }
    return NULL;
}

void *client_send(void *arg)
{
    int cnt = 1;
    while (flag_send == 0)
    {
        char request[BUFFER_SIZE];
        snprintf(request, BUFFER_SIZE, "Запрос %d", cnt++);
        int send_result = send(interaction_socket, request, BUFFER_SIZE, 0);
        if (send_result == -1)
        {
            perror("Ошибка при отправке данных");
        }
        else
        {
            printf("Запрос, отправленный клиентом на сервер: %s\n", request);
        }
        sleep(1);
    }
    return NULL;
}

void *client_connection(void *arg)
{
    printf("Клиент ожидает соединения\n");

    while (flag_wait_conn == 0)
    {
        struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT);
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        int conn_res = connect(interaction_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
        if (conn_res == -1)
        {
            perror("Ошибка соединения");
            sleep(1);
        }
        else
        {
            pthread_t send_thread, get_thread;

            if (pthread_create(&send_thread, NULL, client_send, NULL) != 0)
            {
                perror("Ошибка при создании потока отправки");
                continue;
            }
            if (pthread_create(&get_thread, NULL, client_get, NULL) != 0)
            {
                perror("Ошибка при создании потока получения");
                pthread_cancel(send_thread);
                continue;
            }

            pthread_join(send_thread, NULL);
            pthread_join(get_thread, NULL);
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{
    signal(SIGPIPE, sig_handler);
    pthread_t wait_conn;

    interaction_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (interaction_socket == -1)
    {
        perror("Ошибка создания рабочего сокета");
        exit(EXIT_FAILURE);
    }

    fcntl(interaction_socket, F_SETFL, O_NONBLOCK);
    printf("Рабочий сокет успешно создан\n");

    struct sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(7001);
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.2");

    if (bind(interaction_socket, (struct sockaddr *)&clientAddr, sizeof(clientAddr)) == -1)
    {
        perror("Ошибка привязки");
        close(interaction_socket);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in clientName;
    socklen_t len = sizeof(clientName);
    getsockname(interaction_socket, (struct sockaddr *)&clientName, &len);
    printf("Адрес клиента: %s\n", inet_ntoa(clientName.sin_addr));
    printf("Порт клиента: %d\n", ntohs(clientName.sin_port));

    if (pthread_create(&wait_conn, NULL, client_connection, NULL) != 0)
    {
        perror("Ошибка при создании потока соединения");
        close(interaction_socket);
        exit(EXIT_FAILURE);
    }

    getchar();
    flag_wait_conn = 1;
    flag_get = 1;
    flag_send = 1;

    pthread_join(wait_conn, NULL);

    printf("Работа клиента завершена\n");
    close(interaction_socket);
    return 0;
}
