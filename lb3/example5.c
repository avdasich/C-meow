#include <stdio.h>

int main() {
    int a;
    int s = 0;

    printf("Введите число: ");
    scanf("%d", &a);

    for (int n = 2; n < a; n++) {
        if (a % n == 0) {
            s++;
        }
    }

    if (s == 0) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}
