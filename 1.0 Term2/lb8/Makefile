CC = clang
CFLAGS = -Wall -Wextra -g
INCLUDES = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lcmocka

# Таргет для компиляции тестов
all: test

# Компиляция тестов
test: lb8_test.c lb8.c
	$(CC) $(CFLAGS) lb8_test.c lb8.c $(INCLUDES) $(LDFLAGS) -o lb8_test

# Очистка
clean:
	rm -f lb8_test
