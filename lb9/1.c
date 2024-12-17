#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//функция для проверки ввода числа
int true_input_int() {
    int num;
    while (1) {
        if (scanf("%d", &num) == 1) { //проверяем, что ввод был числом
            return num;  //возвращение введенного числа
        } else {
            printf("Неверный ввод:0 Еще раз: ");
            //очистка буфера ввода
            while (getchar() != '\n');
        }
    }
}

//создание матрицы
void create_matrix(int rows, int cols, int **matrix) {
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 21;
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }
}


//ручной ввод матрицы
void input_matrix(int rows, int cols, int **matrix) {
    printf("Введите элементы матрицы (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Элемент [%d] [%d]: ", i + 1, j + 1);
            matrix[i][j] = true_input_int();  //ввод с проверкой
        }
    }
}


//вывод матрицы
void print_matrix(int rows, int cols, int **matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }
}

//проверка на нули
void check_matrix(int rows, int cols, int **matrix) {
    bool all_zero = false; //переменная для проверки

    for (int i = 0; i < rows; i++) {
        bool row_has_zero = false;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                all_zero = true;
                row_has_zero = true;
            }
        }
        if (row_has_zero) {
            printf("Нули есть в %d-ой строке\n", i + 1);
        }
    }

    if (!all_zero) {
        printf("Не было найдено нулей\n");
    }
}

//среднее арифметическое
void arithmetic_mean(int rows, int cols, int **matrix) {
    int res = 0;
    int elemets_matrix = rows * cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res += matrix[i][j];
        }
    }

    float res_arithmetic_mean = (float)res / elemets_matrix;
    printf("Среднее арифметическое матрицы: %.2f\n", res_arithmetic_mean);
}

//смена диагоналей
void swap_elements(int rows, int cols, int **matrix) {
    if (rows == cols) {
        for (int i = 0; i < rows; i++) { //для квадратной матрицы
            int n = matrix[i][i];
            matrix[i][i] = matrix[i][cols - i - 1];
            matrix[i][cols - i - 1] = n;
        }
        printf("Измененная матрица:\n");
    } else {
        for (int j = 0; j < cols; j++) {
            int m = matrix[0][j];
            matrix[0][j] = matrix[rows - 1][j];
            matrix[rows - 1][j] = m;
        }
        printf("Измененная матрица\n");
    }
}

//вывод
int main(void) {
    int rows, cols, choice;

    //ввод с проверкой
    printf("Введите количество строк: ");
    rows = true_input_int();  //ввод с проверкой

    printf("Введите количество столбцов: ");
    cols = true_input_int();  //ввод с проверкой

    if (rows <= 0 || cols <= 0) {
        printf("Некорректный размер матрицы:0\n");
        return 1;
    }

    //выделение памяти
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (size_t i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    printf("Выберите вариант заполнения матрицы:\n");
    printf("1. Случайная матрица\n");
    printf("2. Ручной ввод\n");
    printf("\n");

    //ввод с проверкой
    printf("Ваш выбор: ");
    choice = true_input_int();  
    printf("\n");

    if (choice == 1) {
        printf("Случайная матрица:\n");
        create_matrix(rows, cols, matrix);
    } else if (choice == 2) {
        input_matrix(rows, cols, matrix);
    } else {
        printf("Неверный выбор:0\n");
        return 1;
    }

    printf("Полученная матрица:\n");
    print_matrix(rows, cols, matrix);
    printf("\n");

    check_matrix(rows, cols, matrix);
    arithmetic_mean(rows, cols, matrix);
    printf("\n");

    swap_elements(rows, cols, matrix);
    printf("Измененная матрица:\n");
    print_matrix(rows, cols, matrix);
    printf("\n");

    //oсвобождение памяти
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
