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
                if (current_lines >= max_lines) {
                    printf("Помилка: Досягнуто ліміт рядків. Неможливо додати новий.");
                }
                else {
                    current_lines ++;
                    a[current_lines-1] = malloc(max_length * sizeof(char));
                    a[current_lines-1][0] = '\0';
                    printf("Ви почали новий рядок");
                }

                break;
            case 3: {
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
            }
            case 4:
                char filename_2[100];
                printf("Введіть ім'я файлу для збереження: ");
                scanf("%s", filename_2);

                FILE* file_2 = fopen(filename_2, "r");

                if (file_2 != NULL) {
                    current_lines = 0;
                    char temp_buffer[128];
                    while (fgets(temp_buffer, 128, file_2) != NULL) {
                        temp_buffer[strcspn(temp_buffer, "\n")] = '\0';
                        a[current_lines] = malloc(128*sizeof(char));
                        strcpy(a[current_lines], temp_buffer);
                        current_lines ++;
                    }
                    fclose(file_2);
                    printf("Текст успішно завантажено\n");
                }
                else {
                    printf("Помилка під час відкриття файлу\n");
                }
                break;
            case 5:
                for (int i=0; i < current_lines; i++) {
                    printf("%s \n", a[i]);
                }
                break;
            case 6:
                int insert_line, insert_index;
                char insert_text[128];
                printf("Виберіть рядок та індекс: ");
                scanf("%d %d", &insert_line, &insert_index);
                printf("Введіть текст, який потрібно вставити: ");
                scanf(" %[^\n]", insert_text);

                if (insert_line < 0 || insert_line >= current_lines || insert_index < 0 || insert_index > strlen(a[insert_line])) {
                    printf("Помилка: Індекс вставки поза межами діапазону\n");
                }
                else {
                    int old_len = strlen(a[insert_line]);
                    int insert_len = strlen(insert_text);
                    int new_len = old_len + insert_len;
                    a[insert_line] = realloc(a[insert_line], (new_len + 1) * sizeof(char));
                    if (a[insert_line] != NULL) {
                        memmove(a[insert_line] + insert_index + insert_len,
                            a[insert_line] + insert_index,
                            old_len - insert_index + 1);

                        memcpy(a[insert_line] + insert_index, insert_text, insert_len);
                        printf("Текст успішно вставлено!\n");
                    }
                    else {
                        printf("Помилка виділення пам'яті\n");
                    }
                }
                break;
            case 7:
                char search_term[128];
                printf("Введіть текст для пошуку: ");
                scanf(" %[^\n]", search_term);
                for (int i=0; i < current_lines; i++) {
                    char * myPtr = a[i];
                    while ((myPtr = strstr(myPtr, search_term)) != NULL) {
                        int index = myPtr - a[i];
                        printf("У цьому місці міститься текст: %d %d\n", i, index);
                        myPtr += strlen(search_term);
                    }
                }
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