TARGET = data_buffer

all: build run

build:
	gcc -g -Wall -Wextra -Werror -Wpedantic -o $(TARGET) main.c buffer.c

run:
	./$(TARGET)

clean:
	if [ -f $(TARGET) ]; then rm $(TARGET); fi
