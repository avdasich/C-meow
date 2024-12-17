#include <stdio.h>
#include "function.h"

int main(void) {
    int n;
    printf("Введите количество человек: ");
    scanf("%d", &n);

    struct Date dates[n];

    for (int i = 0; i < n; i++) {
        printf("Введите дату рождения (день месяц год) для пипла %d: ", i + 1);
        scanf("%d %d %d", &dates[i].day, &dates[i].month, &dates[i].year);

        info(dates[i]);
    }

    return 0;
}
