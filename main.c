#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help() {
    printf("\n=== Головне меню текстового редактора ===\n");
    printf("1. Додати символи в кінець\n");
    printf("2. Почати новий рядок\n");
    printf("3. Зберегти у файл\n");
    printf("4. Завантажити з файлу\n");
    printf("5. Надрукувати поточний текст на консоль\n");
    printf("6. Вставити текст за індексом рядка та символу\n");
    printf("7. Пошук тексту\n");
    printf("0. Вихід з програми\n");
    printf("=========================================\n");
    printf("Виберіть команду: ");
}

int main(void) {

    int command;
    int running = 1;
    int max_lines = 10;
    int current_lines = 1;
    int max_length = 128;

    char** a = malloc(max_lines*sizeof(char*));
    a[0] = malloc(max_length * sizeof(char));
    a[0][0] = '\0';

    while (running == 1) {
        print_help();
        scanf("%d", &command);

        switch(command) {
            case 1:
                char buffer[128];
                printf("Введіть текст для додавання: ");
                scanf(" %[^\n]", buffer);
                strcat(a[current_lines-1], buffer);
                break;
            case 2:
                current_lines ++;
                a[current_lines-1] = malloc(max_length * sizeof(char));
                a[current_lines-1][0] = '\0';
                printf("Ви почали новий рядок");
                break;
            case 3:
                char filename[100];
                printf("Enter the file name for saving: ");
                scanf("%s", filename);

                FILE* file = fopen(filename, "w");

                if (file != NULL) {

                    for (int i=0; i < current_lines; i++) {
                        fputs(a[i], file);
                        fputs("\n", file);

                    }
                    fclose(file);

                    printf("Текст успішно збережено\n");
                } else {
                    printf("Помилка під час відкриття файлу\n");
                }
                break;
            case 4:
                printf("Завантажити з файлу");
                break;
            case 5:
                for (int i=0; i < current_lines; i++) {
                    printf("%s \n", a[i]);
                }
                break;
            case 6:
                printf("Вставити текст за індексом рядка та символу");
                break;
            case 7:
                printf("Пошук тексту");
                break;
            case 0:
                printf("Вихід з програми");
                running = 0;
                break;
            default:
                printf("Такої команди немає.\n");
                break;
        }
    }
    return 0;
}

