#include <stdio.h>
#include "function.h"

void info(struct Date date) {
    int decade = (date.day - 1) / 10 + 1;
    int century = (date.year / 100) + 1;
    char *season;

    if (date.month == 12 || date.month == 1 || date.month == 2) {
        season = "Зима";
    } else if (date.month == 3 || date.month == 4 || date.month == 5) {
        season = "Весна";
    } else if (date.month == 6 || date.month == 7 || date.month == 8) {
        season = "Лето";
    } else if (date.month == 9 || date.month == 10 || date.month == 11) {
        season = "Осень";
    } else {
        season = "Таких не бывает:0";
    }

    printf("Человек родился в %d-й декаде\nB сезоне: %s\nB %d веке.\n", 
        decade, season, century);
}
