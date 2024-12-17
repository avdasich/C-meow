TARGET = MyProject
CC = gcc

SRC = main.c function.c
OBJ = $(patsubst %.c, %.o, $(SRC))

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(TARGET) *.o

