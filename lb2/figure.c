#include <stdio.h>
int main(void) {
 float  x,y;
printf("Введите Х и У\n"); 
scanf("%f %f", &x, &y);

if(x<=2 && y<=2 && y>=-x) {
	printf("yes\n"); }
else {
	printf("no\n"); }

return 0;
}