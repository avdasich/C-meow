TARGET = MyProject
CC = gcc

SRC = main.c read_pipe.c write_pipe.c background.c
OBJ = $(patsubst %.c, %.o, $(SRC))

# Правило сборки цели
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Правило сборки объектных файлов
%.o: %.c
	$(CC) -c $< -o $@

# Очистка
clean:
	rm -f $(TARGET) *.o
