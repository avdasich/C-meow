#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <locale.h>

#define MAX_INPUT 100

void generate_arithmetic(int level, int *a, int *b, char *op) {
    *a = (level == 1) ? (rand() % 10 + 1) : (rand() % 91 + 10);
    *b = (level == 1) ? (rand() % 10 + 1) : (rand() % 91 + 10);
    int op_choice = (level == 1) ? rand() % 2 : (level == 2) ? rand() % 3 : rand() % 4;
    switch (op_choice) {
        case 0: *op = '+'; break;
        case 1: *op = '-'; break;
        case 2: *op = '*'; break;
        case 3: *op = '/'; while (*b == 0) *b = rand() % 91 + 10; break;
        default: *op = '+'; break;
    }
}

void generate_derivative(int *type, int *a, int *b, int *n, int *x) {
    *type = rand() % 3;
    *x = rand() % 5 + 1;
    if (*type == 0) {
        *a = rand() % 11 - 5;
        *b = rand() % 11 - 5;
        *n = 0;
    } else if (*type == 1) {
        *a = *b = 0;
        *n = rand() % 2 + 2;
    } else {
        *a = rand() % 11 - 5;
        *b = *n = 0;
    }
}

double compute_arithmetic(int a, int b, char op) {
    switch (op) {
        case '+': return (double)(a + b);
        case '-': return (double)(a - b);
        case '*': return (double)(a * b);
        case '/': return (double)a / b;
        default: return 0.0;
    }
}

double compute_derivative(int type, int a, int b, int n, int x) {
    if (type == 0) return (double)a;
    if (type == 1) return n * pow(x, n - 1);
    return 0.0;
}

void print_derivative_problem(int type, int a, int b, int n, int x) {
    printf("Найдите производную f(x) = ");
    if (type == 0) {
        if (a != 0) printf("%dx", a);
        if (b > 0) printf("+%d", b);
        else if (b < 0) printf("%d", b);
        if (a == 0 && b == 0) printf("0");
    } else if (type == 1) {
        printf("x^%d", n);
    } else {
        printf("%d", a);
    }
    printf(" в точке x = %d\n", x);
}

int safe_input_double(double *out) {
    char input[MAX_INPUT];
    if (!fgets(input, sizeof(input), stdin)) return 0;
    return sscanf(input, "%lf", out) == 1;
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    if (argc < 3) {
        printf("Использование: %s <кол-во_заданий> <уровень(1-3)> [файл_результатов]\n", argv[0]);
        return 1;
    }

    int num_puzzles = atoi(argv[1]);
    int level = atoi(argv[2]);
    char *filename = (argc == 4) ? argv[3] : NULL;

    if (num_puzzles <= 0 || level < 1 || level > 3) {
        printf("Ошибка: количество > 0, уровень от 1 до 3\n");
        return 1;
    }

    FILE *fp = NULL;
    if (filename) {
        fp = fopen(filename, "w");
        if (!fp) {
            printf("Не удалось открыть файл %s для записи\n", filename);
            return 1;
        }
    }

    srand((unsigned int)time(NULL));
    int correct = 0;
    double total_time = 0.0;

    if (fp) {
        fprintf(fp, "Результаты упражнений\nКол-во: %d, Уровень: %d\n\n", num_puzzles, level);
    }

    for (int i = 0; i < num_puzzles; i++) {
        int a = 0, b = 0, n = 0, x = 0, type = 0;
        char op = '+';
        double correct_answer = 0.0;

        printf("\nЗадание %d:\n", i + 1);
        int is_derivative = (level == 3 && rand() % 2);

        if (is_derivative) {
            generate_derivative(&type, &a, &b, &n, &x);
            print_derivative_problem(type, a, b, n, x);
            correct_answer = compute_derivative(type, a, b, n, x);
        } else {
            generate_arithmetic(level, &a, &b, &op);
            printf("%d %c %d = ?\n", a, op, b);
            correct_answer = compute_arithmetic(a, b, op);
        }

        time_t start = time(NULL);
        printf("Ваш ответ: ");
        double user_answer = 0.0;

        if (!safe_input_double(&user_answer)) {
            printf("Ошибка ввода. Пропуск задания.\n");
            continue;
        }

        time_t end = time(NULL);
        double time_spent = difftime(end, start);
        total_time += time_spent;

        int is_correct = fabs(user_answer - correct_answer) < 0.01;
        if (is_correct) {
            printf("✅ Верно! (%.2f сек)\n", time_spent);
            correct++;
        } else {
            printf("❌ Неверно. Правильный ответ: %.2f (%.2f сек)\n", correct_answer, time_spent);
            if (is_derivative) {
                if (type == 0) printf("Подсказка: производная от ax+b = a\n");
                else if (type == 1) printf("Подсказка: x^n → n*x^(n-1)\n");
                else printf("Подсказка: производная константы = 0\n");
            } else {
                printf("Подсказка: проверьте арифметику.\n");
            }
        }

        if (fp) {
            if (is_derivative) {
                fprintf(fp, "Задание %d: f(x) = ", i + 1);
                if (type == 0) {
                    if (a != 0) fprintf(fp, "%dx", a);
                    if (b != 0) fprintf(fp, "%+d", b);
                    if (a == 0 && b == 0) fprintf(fp, "0");
                } else if (type == 1) {
                    fprintf(fp, "x^%d", n);
                } else {
                    fprintf(fp, "%d", a);
                }
                fprintf(fp, ", x = %d, Ответ: %.2f, Ваш: %.2f, Время: %.2f сек, %s\n",
                        x, correct_answer, user_answer, time_spent,
                        is_correct ? "✅ Верно" : "❌ Неверно");
            } else {
                fprintf(fp, "Задание %d: %d %c %d = %.2f, Ваш: %.2f, Время: %.2f сек, %s\n",
                        i + 1, a, op, b, correct_answer, user_answer, time_spent,
                        is_correct ? "✅ Верно" : "❌ Неверно");
            }
        }
    }

    double avg_time = (num_puzzles > 0) ? total_time / num_puzzles : 0;

    printf("\n📊 Итоги:\n");
    printf("Правильных ответов: %d из %d (%.2f%%)\n", correct, num_puzzles, 100.0 * correct / num_puzzles);
    printf("Общее время: %.2f сек\n", total_time);
    printf("Среднее время: %.2f сек\n", avg_time);

    if (fp) {
        fprintf(fp, "\nИтоги:\n");
        fprintf(fp, "Правильных: %d из %d (%.2f%%)\n", correct, num_puzzles, 100.0 * correct / num_puzzles);
        fprintf(fp, "Общее время: %.2f сек\n", total_time);
        fprintf(fp, "Среднее время: %.2f сек\n", avg_time);
        fclose(fp);
        printf("Результаты сохранены в %s\n", filename);
    }

    return 0;
}
