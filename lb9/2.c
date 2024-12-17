#include <stdio.h>
int main(void){

size_t var = sizeof(int);
size_t var2 = sizeof(char);
size_t var3 = sizeof(float);
size_t var4 = sizeof(double);

printf("var = %zu\n", var);
printf("var2 = %zu\n", var2);
printf("var3 = %zu\n", var3);
printf("var4 = %zu\n", var4);
    return 0;
}