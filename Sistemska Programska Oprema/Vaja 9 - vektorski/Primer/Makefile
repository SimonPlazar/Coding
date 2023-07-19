all: build

build:
	gcc -mavx2 -O2 -o main_o2 main.c
	gcc -mavx2 -o main main.c

run:
	./main
	./main_o2