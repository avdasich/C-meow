#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void* basic_thread_func(void* arg) {
    for (int i = 5; i < 10; i++) {
        printf("Дочерний поток: %d\n", i);
    }
    return NULL;
}

void* join_thread_func(void* arg) {
    for (int i = 1; i < 5; i++) {
        printf("Поток с ожиданием: %d\n", i);
    }
    return NULL;
}

void* param_thread_func(void* arg) {
    char* msg = (char*)arg;
    for (int i = 0; i < 5; i++) {
        printf("%s: %d\n", msg, i);
    }
    return NULL;
}

void cleanup_handler(void* arg) {
    printf("Очистка: Поток %ld завершен\n", (long)arg);
}

void* cancel_thread_func(void* arg) {
    pthread_cleanup_push(cleanup_handler, arg);
    
    for (int i = 0; i < 5; i++) {
        printf("Поток %ld: %d\n", (long)arg, i);
        sleep(1);
    }
    
    pthread_cleanup_pop(0);
    return NULL;
}

void* sleep_sort_func(void* arg) {
    int num = *(int*)arg;
    usleep(num * 100000); 
    printf("%d ", num);
    return NULL;
}

int main() {
    printf("Создание потока\n\n");
    pthread_t thread1;
    pthread_create(&thread1, NULL, basic_thread_func, NULL);
    
    for (int i = 0; i < 5; i++) {
        printf("Основной поток: %d\n", i);
    }
    pthread_join(thread1, NULL);
    
    printf("\nОжидание потока\n\n");
    pthread_t thread2;
    pthread_create(&thread2, NULL, join_thread_func, NULL);
    pthread_join(thread2, NULL);
    
    for (int i = 0; i < 5; i++) {
        printf("Основной поток после ожидания: %d\n", i);
    }
    
    printf("\nПараметры потока\n\n");
    pthread_t threads[4];
    char* messages[] = {"Поток 1", "Поток 2", "Поток 3", "Поток 4"};
    
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, param_thread_func, messages[i]);
    }
    
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\nОтмена потока с обработчиком\n\n");
    pthread_t cancel_threads[4];
    
    for (long i = 0; i < 4; i++) {
        pthread_create(&cancel_threads[i], NULL, cancel_thread_func, (void*)i);
    }
    
    sleep(2); 
    for (int i = 0; i < 4; i++) {
        pthread_cancel(cancel_threads[i]);
    }
    
    for (int i = 0; i < 4; i++) {
        pthread_join(cancel_threads[i], NULL);
    }
    
    printf("\n\nSleepsort\n\n");
    int arr[] = {3, 1, 4, 2, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    pthread_t sleep_threads[n];
    
    printf("Изначальный массив: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    
    printf("\nОтсортированный массив: ");
    for (int i = 0; i < n; i++) {
        pthread_create(&sleep_threads[i], NULL, sleep_sort_func, &arr[i]);
    }
    
    for (int i = 0; i < n; i++) {
        pthread_join(sleep_threads[i], NULL);
    }
    
    printf("\n");
    return 0;
}