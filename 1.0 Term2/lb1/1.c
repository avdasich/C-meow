#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 10

struct Student {
    char student_name[64];
    signed char math_score;     //мат-ка
    signed char physics_score; //физ-ка
    signed char inf_score;     //инф-ка
    int total_score;           //общий(всего)
};

struct Student addNewStudent(char *name, signed char math, signed char phy, signed char inf) {
    struct Student newStudent;
    strncpy(newStudent.student_name, name, 64);
    newStudent.math_score = math;
    newStudent.physics_score = phy;
    newStudent.inf_score = inf;
    newStudent.total_score = math + phy + inf;
    return newStudent;
}

void printStudentInfo(struct Student student) {
    printf("Имя: %-15s Общий балл: %d\n", student.student_name, student.total_score);
}

void selectionSort(struct Student *students, int *ts) {
    int t1 = clock();
    for (int i = 0; i < N-1; i++) {
        int max_index = i;
        for (int j = i + 1; j < N; j++) {
            if (students[j].total_score > students[max_index].total_score) {
                max_index = j;
            }
        }
        if (max_index != i) {
            struct Student temp = students[i];
            students[i] = students[max_index];
            students[max_index] = temp;
        }
    }
    int t2 = clock();
    *ts = t2 - t1;
}

void countingSort(struct Student *students, int *tc) {
    int t1 = clock();
    int count[301] = {0};
    struct Student *output = malloc(N * sizeof(struct Student));

    for (int i = 0; i < N; i++)
        count[students[i].total_score]++;

    for (int i = 1; i <= 300; i++)
        count[i] += count[i-1];

    for (int i = N-1; i >= 0; i--) {
        output[count[students[i].total_score]-1] = students[i];
        count[students[i].total_score]--;
    }

    for (int i = 0; i < N; i++)
        students[i] = output[N-i-1];

    free(output);
    int t2 = clock();
    *tc = t2 - t1;
}

void Fill(struct Student *students) {
    for (int i = 0; i < N; i++) {
        char name[20];
        snprintf(name, sizeof(name), "Студент %d", i + 1);
        students[i] = addNewStudent(
            name,
            rand() % 101,
            rand() % 101,
            rand() % 101
        );
    }
}

int main() {
    srand(time(NULL));

    struct Student students[100000];

    //для N = 100

    printf("Тестирование для N = 100\n");

    Fill(students);
    printf("\nДо сортировки:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }

    int ts, tc;
    selectionSort(students, &ts);
    printf("\nПосле сортировки выбором:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }

    Fill(students);
    countingSort(students, &tc);
    printf("\nПосле сортировки подсчетом:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }

    printf("\nВремя выполнения (N=100):\n");
    printf("Сортировка выбором:   %.6f сек\n", (float)ts / CLOCKS_PER_SEC);
    printf("Сортировка подсчетом: %.6f сек\n", (float)tc / CLOCKS_PER_SEC);

    //тестирование для N = 10000
    #undef N
    #define N 10000
    printf("\nТестирование для N = 10000\n");
    

    Fill(students);
    selectionSort(students, &ts);
    Fill(students);
    countingSort(students, &tc);

    printf("\nВремя выполнения (N=10000):\n");
    printf("Сортировка выбором:   %.6f сек\n", (float)ts / CLOCKS_PER_SEC);
    printf("Сортировка подсчетом: %.6f сек\n", (float)tc / CLOCKS_PER_SEC);

    //для N = 100000
    #undef N
    #define N 100000
    printf("\nТестирование для N = 100000\n");
   

    Fill(students);
    selectionSort(students, &ts);
    Fill(students);
    countingSort(students, &tc);

    printf("\nВремя выполнения (N=100000):\n");
    printf("Сортировка выбором:   %.6f сек\n", (float)ts / CLOCKS_PER_SEC);
    printf("Сортировка подсчетом: %.6f сек\n", (float)tc / CLOCKS_PER_SEC);

    //системная информация
    printf("Характеристики системы:\n");
    system("sysctl -n machdep.cpu.brand_string");
    system("sysctl -n hw.ncpu");
    
    return 0;
}