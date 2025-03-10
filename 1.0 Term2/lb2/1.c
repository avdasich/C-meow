#include <stdio.h>
#include <stdlib.h>

//осн. структура
struct node {
    int data;
    struct node *next;
    struct node *another; 
};


void append(struct node **head, int data) {
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->another = NULL; 

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    struct node *last = *head;
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
}

//вывод списка на экран
void print_list(struct node *head) {
    struct node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
//связка двух списков
void link_lists(struct node *head1, struct node *head2) {
    struct node *current1 = head1;
    struct node *current2 = head2;

    while (current1 != NULL && current2 != NULL) {
        current1->another = current2;
        current1 = current1->next;
        current2 = current2->next;
    }
}

//начало с конца списка
struct node* get_last_node(struct node *head) {
    struct node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

// переходы по спискам
void navigate(struct node *head1, struct node *head2) {
    struct node *current = get_last_node(head1); //конец первого списка(начало)
    char input;
    int in_second_list = 0; 

    while (1) {
        printf("\nТекущее значение: %d\n", current->data);
        if (!in_second_list) {
            printf("Тык (A - влево, S - второй список, Q - выхода): ");
        } else {
            printf("Тап (D - вправо, Q - выход): ");
        }
        scanf(" %c", &input);

        if (input == 'Q' || input == 'q') {
            printf("The end\n");
            exit(0); 
        } else if (!in_second_list) {
            
            if (input == 'A' || input == 'a') { //переходы(влево) по первому списку
                if (current != head1) {
                    struct node *temp = head1;
                    while (temp->next != current) {
                        temp = temp->next;
                    }
                    current = temp;
                } else {
                    printf("А вот и конец первого списка\n");
                }
            } else if (input == 'S' || input == 's') {
                if (current->another != NULL) {
                    //переход на второй список
                    current = current->another;
                    in_second_list = 1; 
                    printf("Телепорт на второй список\n");
                } else {
                    printf("Пути назад нет /:\n");
                }
            } else {
                printf("Туда путь закрыт\n");
            }
        } else {
            //переходы(вправо) во втором списке
            if (input == 'D' || input == 'd') {
                if (current->next != NULL) {
                    current = current->next;
                } else {
                    printf("\nА это уже конец второго списка.\n");
                }
            } else {
                printf("\nИ туда нельзя :0\n");
            }
        }
    }
}

int main() { //главня функция
    struct node *head1 = NULL;
    struct node *head2 = NULL;
    int input;

    printf("Введи чо-нибудь для первого списка (0 для выхода отседа):\n");
    while (1) {
        scanf("%d", &input);
        if (input == 0) break;
        append(&head1, input);
    }

    printf("Введи чо-нибудь для второго списка (0 для выхода отседа):\n");
    while (1) {
        scanf("%d", &input);
        if (input == 0) break;
        append(&head2, input);
    }

    printf("Первый список: ");
    print_list(head1);
    printf("Второй список: ");
    print_list(head2);

    link_lists(head1, head2);
    printf("Списки готовы.\n");

    navigate(head1, head2);

    return 0;
}