TARGET = my_exec

all: build run

build:
	gcc -g -Wall -Wextra -Werror -Wpedantic -o $(TARGET) main.c my_func.c

run:
	./$(TARGET)

clean:
	if [ -f $(TARGET) ]; then rm $(TARGET); fi
