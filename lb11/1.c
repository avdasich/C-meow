#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uinit;

uinit a;
void *init(int* arr, int n){ //cоздание функции инит 

arr = malloc(n * sizeof(int)); //рассчет для выделния памяти
for (long i = 0; i < n; ++i) { 
    arr[i] = i;
        
    }
return arr; // возврат на  массив arr из функции init
}

int main() {

int* arr = NULL;
int n = 10;

arr = init(arr, n);
for (int i = 0; i < n; ++i) {
    printf("%d\n", arr[i]);
}
free(arr);
return 0;
}
