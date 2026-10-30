CC = gcc.exe
CFLAGS = -Wall -Werror -Wshadow
TARGET = hash_calc.exe
SRC = main.c include/functions.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	del $(TARGET)

