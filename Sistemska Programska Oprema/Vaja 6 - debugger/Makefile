TARGET = spo_debug

all: build run

build:
	gcc -m32 -fPIE -g -Wall -Wextra -o spo_debug main.c

run:
	./$(TARGET)

clean:
	if [ -f $(TARGET) ]; then rm -f $(TARGET); fi

test:
	./$(TARGET) test_debug
