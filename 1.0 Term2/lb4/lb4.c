#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000
#define MAX_WORD_LENGTH 100
#define NAME "DANIL"

//функция замены самого длинного слова на NAME
void replace_longest_word(char *line) {
    char longest_word[MAX_WORD_LENGTH] = "";
    char current_word[MAX_WORD_LENGTH] = "";
    int longest_length = 0;
    int current_length = 0;
    int in_word = 0;
    int line_len = strlen(line);
    int word_start = 0;

    for (int i = 0; i <= line_len; i++) {
        if (isalpha(line[i])) {
            if (!in_word) {
                in_word = 1;
                word_start = i;
            }
            current_word[current_length++] = line[i];
        } else {
            if (in_word) {
                current_word[current_length] = '\0';
                if (current_length > longest_length) {
                    longest_length = current_length;
                    strcpy(longest_word, current_word);
                }
                current_length = 0;
                in_word = 0;
            }
        }
    }

    if (longest_length > 0) {
        char new_line[MAX_LINE_LENGTH] = "";
        char *ptr = line;
        char *found;

        while ((found = strstr(ptr, longest_word)) != NULL) {
            strncat(new_line, ptr, found - ptr);
            strcat(new_line, NAME);
            ptr = found + longest_length;
        }
        strcat(new_line, ptr);
        strcpy(line, new_line);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Использование: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Ошибка при открытии файла :/");
        return 1;
    }

    // Читаем все строки в массив
    char lines[1000][MAX_LINE_LENGTH];
    int line_count = 0;


    while (fgets(lines[line_count], sizeof(lines[0]), file)) {
        lines[line_count][strcspn(lines[line_count], "\n")] = '\0'; // Удаляем \n
        replace_longest_word(lines[line_count]);
        line_count++;
    }
    fclose(file);

    // Перезаписываем файл
    file = fopen(argv[1], "w");
    if (file == NULL) {
        perror("Ошибка");
        return 1;
    }

    for (int i = 0; i < line_count; i++) {
        fprintf(file, "%s\n", lines[i]);
    }
    fclose(file);

    printf("файл готов, слова заменены на '%s'.\n", NAME);
    return 0;
}