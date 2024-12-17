#include <stdio.h>

int main(){

 int g = 1;
 int a, i, n;

 printf("Введите высоту прямоугольника:");
 scanf("%d", &a);

 for (i = 0; i != a; i++){ //задаем количество строк 
  for (n = 0; n != a; n++){ //задаем количество столбов 
   printf("%d ", g);
   g++; //к переменоой добавялем +1 после каждого круга цикла 
  }
  printf("\n");
 }
 printf("\n");

 return 0;
}
