TARGET = "elf_loader"

all: build run

build: build_elf_loader build_hello

build_elf_loader:
	gcc -g -Wall -Wextra -Wpedantic -Werror -o $(TARGET) main.c elf_loader.c

build_hello:
	as -o hello.o hello.asm
	ld -s -o hello hello.o

run:
	./$(TARGET) -r hello

clean:
	if [ -f $(TARGET) ]; then rm $(TARGET); fi
	if [ -f hello.o ]; then rm hello.o; fi
	if [ -f hello ]; then rm hello; fi