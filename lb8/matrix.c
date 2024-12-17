#include <stdio.h>

int matrix_length(int matrix[])
{
    int count = 0;
    for(int i=0; matrix[i]!='\0'; i++)
    {
        count++;
    }
    return count;
}

int main() {
    int n;
    printf("Введите размер матрицы: ");
    scanf("%d", &n);

    int matrix[n][n];
    int value = 1;
    int length = sizeof(matrix) / sizeof(matrix[0]);
    int h;

    // Заполнение матрицы числами по нарастающей
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[j][i] = value;
            value++;
        }
     
    }
    
    int m;
 
    m = matrix_length(matrix);
    printf("Длина массива: %d\n", m);
    printf("Размер массива: %d\n", length);
    printf("Матрица %dx%d:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    

    return 0;
}