#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    printf("\n\nНачало работы 9_setuid.c\n\n");

    printf("\n\nначало работы функции setuid() в 9_setuid.c\n\n");
    if (setuid(0) == -1) {
        perror("Ошибка setuid");
        printf("\n\nКонец работы функции setuid() в 9_setuid.c\n\n");
        return 1;
    }
    printf("setuid успешно выполнена\n");
    printf("\n\nКонец работы функции setuid() в 9_setuid.c\n\n");

    printf("\n\nКонец работы 9_setuid.c\n\n");
    return 0;
}
