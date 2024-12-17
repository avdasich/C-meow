#include <stdio.h>

int main() {

	float(temperature);
	char(scale);

	printf("Введите температуру: ");
	scanf("%f", &temperature);
	printf("Введите 'c/C' для цельсия или 'f/F' для фарингейта: ");
	scanf(" %c", &scale);

	if (scale == 'c' || scale == 'C') {
	printf("%2f градусов Цельсия =%2f градусов Фарингейта\n", temperature, (temperature * 9 / 5) + 32);
	}
	else if (scale == 'f' || scale == 'F') {
	printf("%2f градусов Фарингейта =%2f градусов Цельсия\n", temperature, (temperature - 32) * 5 / 9);
	}
	else {
	printf("Ошибка, введён недопстимый символ.\n");
}

	return 0;

}
