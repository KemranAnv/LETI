#include <stdio.h>
#include <sys/capability.h>

void view_capabilities(const char *filename) {
    printf("\n\nНачало работы функции view_capabilities() в 9_cap.c\n\n");

    printf("\n\nначало работы функции cap_get_file(filename) в 9_cap.c\n\n");
    cap_t caps = cap_get_file(filename);
    if (caps == NULL) {
        perror("Ошибка cap_get_file");
        printf("\n\nКонец работы функции cap_get_file(filename) в 9_cap.c\n\n");
        return;
    }

    ssize_t length;
    char *text_caps = cap_to_text(caps, &length);
    if (text_caps) {
        printf("Возможности %s: %s\n", filename, text_caps);
        cap_free(text_caps);
    }
    cap_free(caps);

    printf("\n\nКонец работы функции view_capabilities() в 9_cap.c\n\n");
}

void set_capabilities(const char *filename, const char *cap_text) {
    printf("\n\nНачало работы функции set_capabilities() в 9_cap.c\n\n");

    cap_t caps = cap_from_text(cap_text);
    if (caps == NULL) {
        perror("Ошибка cap_from_text");
        printf("\n\nКонец работы функции cap_from_text(cap_text) в 9_cap.c\n\n");
        return;
    }

    if (cap_set_file(filename, caps) == -1) {
        perror("Ошибка cap_set_file");
    }
    cap_free(caps);

    printf("\n\nКонец работы функции set_capabilities() в 9_cap.c\n\n");
}

int main(int argc, char *argv[]) {
    printf("\n\nНачало работы 9_cap.c\n\n");

    if (argc != 3) {
        fprintf(stderr, "Использование: %s <имя файла> <возможности>\nПример: %s ./9_setuid cap_net_admin=+ep\n", argv[0], argv[0]);
        return 1;
    }

    view_capabilities(argv[1]);
    set_capabilities(argv[1], argv[2]);
    view_capabilities(argv[1]);

    printf("\n\nКонец работы 9_cap.c\n\n");
    return 0;
}
