#include <stdio.h> 
int main() {
    int a;
    int n;
    printf("Введите число: ");
    scanf("%d", &a);

    for (n = 2; n < a && a % n != 0; n++);// приравниваем n=2 и проверяем 2 условия, где n меньше а и 
    // чтобы число a не делилось на n без остатка. Далее увеличивает n на 1 после каждой круга, 
    //если оба условия верны.

    if (n == a) 
        printf("1\n");
    else 
        printf("0\n");

    return 0;
}