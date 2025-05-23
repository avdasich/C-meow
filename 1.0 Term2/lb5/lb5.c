#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 50
#define FILENAME "Spravka.dat"

typedef struct {
    char start_point[MAX_LENGTH];
    char end_point[MAX_LENGTH];
    int route_number;
} Route;

void write_routes_to_file(int n) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == 0) {
        printf("Ошибка при создании файла!\n");
        exit(1);
    }

    Route route;
    for (int i = 0; i < n; i++) {
        printf("\nВведите данные для маршрута #%d:\n", i + 1);
        printf("Начальный пункт: ");
        scanf("%s", route.start_point);
        printf("Конечный пункт: ");
        scanf("%s", route.end_point);
        printf("Номер маршрута: ");
        scanf("%d", &route.route_number);

        fwrite(&route, sizeof(Route), 1, file);
    }

    fclose(file);
    printf("\nДанные успешно записаны в файл %s\n", FILENAME);
}

void search_in_file() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == 0) {
        printf("Файл не найден!\n");
        return;
    }

    int choice;
    printf("\nПо какому полю выполнить поиск?\n");
    printf("1. Начальный пункт\n");
    printf("2. Конечный пункт\n");
    printf("3. Номер маршрута\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);

    Route route;
    int found = 0;
    char search_str[MAX_LENGTH];
    int search_num;

    switch (choice) {
        case 1:
            printf("Введите начальный пункт для поиска: ");
            scanf("%s", search_str);
            printf("\nРезультаты поиска:\n");
            while (fread(&route, sizeof(Route), 1, file)) {
                if (strcmp(route.start_point, search_str) == 0) {
                    printf("Начальный пункт: %s, Конечный пункт: %s, Номер маршрута: %d\n",
                           route.start_point, route.end_point, route.route_number);
                    found = 1;
                }
            }
            break;
        case 2:
            printf("Введите конечный пункт для поиска: ");
            scanf("%s", search_str);
            printf("\nРезультаты поиска:\n");
            while (fread(&route, sizeof(Route), 1, file)) {
                if (strcmp(route.end_point, search_str) == 0) {
                    printf("Начальный пункт: %s, Конечный пункт: %s, Номер маршрута: %d\n",
                           route.start_point, route.end_point, route.route_number);
                    found = 1;
                }
            }
            break;
        case 3:
            printf("Введите номер маршрута для поиска: ");
            scanf("%d", &search_num);
            printf("\nРезультаты поиска:\n");
            while (fread(&route, sizeof(Route), 1, file)) {
                if (route.route_number == search_num) {
                    printf("Начальный пункт: %s, Конечный пункт: %s, Номер маршрута: %d\n",
                           route.start_point, route.end_point, route.route_number);
                    found = 1;
                }
            }
            break;
        default:
            printf("Неверный выбор!\n");
    }

    if (!found) {
        printf("Записи не найдены.\n");
    }

    fclose(file);
}

int main() {
    int n;
    printf("Введите количество маршрутов: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Количество маршрутов должно быть положительным числом. Программа завершена.\n");
        return 0;
    }

    write_routes_to_file(n);
    search_in_file();

    return 0;
}
