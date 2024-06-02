#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>
#include <sys/inotify.h>
#include <signal.h>
#include <ev.h>

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct {
    int flag;
    char sym;
} ThreadArgs;

int pipefd[2];
int inotify_fd, watch_fd;

// Обработчик события таймера
static void timer_cb(EV_P_ ev_timer *w, int revents) {
    ThreadArgs *args = (ThreadArgs *) w->data;
    char buff[256];

    int g_t_s = getdtablesize();
    sprintf(buff, "Размер таблицы дескрипторов: %d", g_t_s);

    ssize_t nw = write(pipefd[1], buff, strlen(buff) + 1);
    if (nw > 0)
        printf("Записано %zd байт в канал\n", nw);
    else if (nw == -1)
        perror("Ошибка записи: ");

    if (args->flag == 1) {
        ev_timer_stop(EV_A_ w);
        ev_break(EV_A_ EVBREAK_ALL);
    }
}

// Обработчик события ввода/вывода
static void io_cb(EV_P_ ev_io *w, int revents) {
    ThreadArgs *args = (ThreadArgs *) w->data;
    char buff[256];

    ssize_t nr = read(pipefd[0], buff, sizeof(buff));
    if (nr == 0)
        printf("Конец файла\n");
    else if (nr == -1)
        perror("Ошибка чтения: ");
    else if (nr > 0)
        printf("Прочитано %zd байт из канала: %s\n", nr, buff);

    if (args->flag == 2) {
        ev_io_stop(EV_A_ w);
        ev_break(EV_A_ EVBREAK_ALL);
    }
}

// Обработчик события ввода из stdin
static void stdin_cb(EV_P_ ev_io *w, int revents) {
    ThreadArgs *args = (ThreadArgs *) w->data;
    char buff[256];

    ssize_t nr = read(w->fd, buff, sizeof(buff));
    if (nr > 0) {
        printf("Нажата клавиша: %s\n", buff);
        args->flag = 1;
    }

    ev_io_stop(EV_A_ w);
}

// Обработчик события inotify
static void inotify_cb(EV_P_ ev_io *w, int revents) {
    char buffer[1024];
    ssize_t length = read(inotify_fd, buffer, sizeof(buffer));
    if (length < 0) {
        perror("Ошибка чтения inotify: ");
    }

    struct inotify_event *event = (struct inotify_event *) buffer;
    if (event->mask & IN_MODIFY) {
        printf("Изменение в наблюдаемом файле.\n");
        ev_io_stop(EV_A_ w);
        ev_break(EV_A_ EVBREAK_ALL);
    }
}

void sig_handler(int signo) {
    printf("\n\nПолучен SIGINT; %d\n", signo);
    close(pipefd[0]);
    close(pipefd[1]);
    close(inotify_fd);
    exit(0);
}

int main(int argc, char const *argv[]) {
    printf("Программа начала работу\n");

    signal(SIGINT, sig_handler);

    ThreadArgs args_1, args_2;
    args_1.flag = 0;
    args_1.sym = '1';
    args_2.flag = 0;
    args_2.sym = '2';

    int rv = pipe(pipefd);
    if (rv == -1)
        perror("Ошибка создания канала: ");

    fcntl(pipefd[0], F_SETFL, O_NONBLOCK);
    fcntl(pipefd[1], F_SETFL, O_NONBLOCK);

    struct ev_loop *loop = EV_DEFAULT;
    ev_io stdin_watcher;
    ev_io io_watcher;
    ev_io inotify_watcher;
    ev_timer timer_watcher;

    // Настройка обработчика события ввода из stdin
    ev_io_init(&stdin_watcher, stdin_cb, STDIN_FILENO, EV_READ);
    ev_io_start(loop, &stdin_watcher);
    stdin_watcher.data = &args_1;

    // Настройка обработчика события ввода/вывода для канала
    ev_io_init(&io_watcher, io_cb, pipefd[0], EV_READ);
    ev_io_start(loop, &io_watcher);
    io_watcher.data = &args_2;

    // Настройка обработчика события таймера
    ev_timer_init(&timer_watcher, timer_cb, 1.0, 2.0);
    ev_timer_start(loop, &timer_watcher);
    timer_watcher.data = &args_1;

    // Настройка inotify для наблюдения изменений в текущем каталоге
    inotify_fd = inotify_init1(IN_NONBLOCK);
    if (inotify_fd < 0) {
        perror("Ошибка инициализации inotify: ");
    }

    watch_fd = inotify_add_watch(inotify_fd, ".", IN_MODIFY);
    if (watch_fd < 0) {
        perror("Ошибка добавления наблюдения inotify: ");
    }

    ev_io_init(&inotify_watcher, inotify_cb, inotify_fd, EV_READ);
    ev_io_start(loop, &inotify_watcher);

    // Перевод stdin в неблокирующий режим
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    // Запуск цикла обработки событий
    ev_run(loop, 0);

    close(pipefd[0]);
    close(pipefd[1]);
    close(inotify_fd);

    printf("\n\nПрограмма закончила работу\n");

    return 0;
}
