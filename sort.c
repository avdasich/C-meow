//Сортировка пузырьком 
//обновленный sort
#include <stdio.h>

void bubbleSort(int arr[], int n);

int main() {
    int a[] = {4, 2, 0};
    int n = sizeof(a) / sizeof(a[0]);
    
    bubbleSort(a, n);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}

