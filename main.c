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
    printf("8. Видалення тексту \n");
    printf("11. Cut\n");
    printf("12. Paste\n");
    printf("13. Copy\n");
    printf("14. Вставка із заміною\n");
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
    char* clipboard = NULL;

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
                int new_len = strlen(a[current_lines-1]) + strlen(buffer) + 1;
                a[current_lines-1] = realloc(a[current_lines-1], new_len * sizeof(char));
                strcat(a[current_lines-1], buffer);
                break;
            case 2:
                if (current_lines >= max_lines) {
                    max_lines *= 2;
                    a = realloc(a, max_lines * sizeof(char*));
                }
                else {
                    current_lines ++;
                    a[current_lines-1] = malloc(1 * sizeof(char));
                    a[current_lines-1][0] = '\0';
                    printf("Ви почали новий рядок");
                }

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
                char filename_2[100];
                printf("Введіть ім'я файлу для збереження: ");
                scanf("%s", filename_2);

                FILE* file_2 = fopen(filename_2, "r");

                if (file_2 != NULL) {
                    current_lines = 0;
                    char temp_buffer[128];
                    while (fgets(temp_buffer, 128, file_2) != NULL) {
                        temp_buffer[strcspn(temp_buffer, "\n")] = '\0';
                        if (current_lines >= max_lines) {
                            max_lines *= 2;
                            a = realloc(a, max_lines * sizeof(char*));
                        }
                        int len = strlen(temp_buffer) + 1;
                        a[current_lines] = malloc(len * sizeof(char));
                        strcpy(a[current_lines], temp_buffer);
                        current_lines++;
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
            case 8:
                int del_line, del_index, del_count;
                printf("Виберіть рядок, індекс та кількість символів:");
                scanf("%d %d %d", &del_line, &del_index, &del_count);

                if (del_line < 0 || del_line >= current_lines || del_index < 0 || del_count < 0 || del_index + del_count > strlen(a[del_line])) {
                    printf("Помилка: Неправильні параметри для видалення\n");
                }
                else {
                    int old_len = strlen(a[del_line]);
                    memmove(a[del_line] + del_index,
                            a[del_line] + del_index + del_count,
                            old_len - del_index - del_count + 1);
                    printf("Текст успішно видалено!\n");
                }
                break;
            case 11:
                int cut_line, cut_index, cut_count;
                printf("Виберіть рядок, індекс та кількість символів: ");
                scanf("%d %d %d", &cut_line, &cut_index, &cut_count);

                if (cut_line < 0 || cut_line >= current_lines || cut_index < 0 || cut_count < 0 || cut_index + cut_count > strlen(a[cut_line])) {
                    printf("Помилка: Неправильні параметри для вирізання\n");
                }
                else {
                    clipboard = realloc(clipboard, (cut_count+1) * sizeof(char));
                    memcpy(clipboard, a[cut_line] + cut_index, cut_count);
                    clipboard[cut_count] = '\0';

                    int old_len = strlen(a[cut_line]);
                    memmove(a[cut_line] + cut_index,
                            a[cut_line] + cut_index + cut_count,
                            old_len - cut_index - cut_count + 1);
                    printf("Текст Вирізано в буфер!\n");
                }

                break;
            case 12:
                if (clipboard == NULL) {
                    printf("Помилка: Буфер обміну порожній!\n");
                    break;
                }
                int pst_line, pst_index;
                printf("Виберіть рядок та індекс: ");
                scanf("%d %d", &pst_line, &pst_index);

                if (pst_line < 0 || pst_line >= current_lines || pst_index < 0 || pst_index > strlen(a[pst_line])) {
                    printf("Помилка: Неправильні параметри для вставки\n");
                }
                else {
                    int old_len = strlen(a[pst_line]);
                    int clip_len = strlen(clipboard);

                    a[pst_line] = realloc(a[pst_line], (old_len + clip_len + 1) * sizeof(char));
                    memmove(a[pst_line] + pst_index + clip_len, a[pst_line] + pst_index, old_len - pst_index + 1);
                    memcpy(a[pst_line] + pst_index, clipboard, clip_len);
                    printf("Текст вставлено з буфера!\n");
                }
                break;
            case 13:
                int cp_line, cp_index, cp_count;
                printf("Виберіть рядок, індекс та кількість символів: ");
                scanf("%d %d %d", &cp_line, &cp_index, &cp_count);
                if (cp_line < 0 || cp_line >= current_lines || cp_index < 0 || cp_count < 0 || cp_index + cp_count > strlen(a[cp_line])) {
                    printf("Помилка: Неправильні параметри для копіювання\n");
                }
                else {
                    clipboard = realloc(clipboard, (cp_count+1) * sizeof(char));
                    memcpy(clipboard, a[cp_line] + cp_index, cp_count);
                    clipboard[cp_count] = '\0';

                    printf("Текст успішно скопійовано");
                }
                break;
            case 14:
                int rep_line, rep_index;
                char rep_text[128];
                printf("Виберіть рядок та індекс: ");
                scanf("%d %d", &rep_line, &rep_index);
                printf("Написати текст: ");
                scanf(" %127[^\n]", rep_text);

                if (rep_line < 0 || rep_line >= current_lines || rep_index < 0 || rep_index > strlen(a[rep_line])) {
                    printf("Неправильний індекс заміни\n");
                }
                else {
                    int old_len = strlen(a[rep_line]);
                    int rep_len = strlen(rep_text);
                    if (rep_index + rep_len > old_len) {
                        a[rep_line] = realloc(a[rep_line], (rep_index + rep_len + 1)* sizeof(char));
                        a[rep_line][rep_index + rep_len] = '\0';

                    }
                    memcpy(a[rep_line] + rep_index, rep_text, rep_len);
                    printf("Текст успішно замінено!\n");
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