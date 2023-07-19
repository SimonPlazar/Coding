TARGET_RAW = demo_raw
TARGET_GCC = demo_gcc

all: build run

build: build_raw build_gcc

run: run_raw run_gcc

clean: clean_raw clean_gcc

# Raw build
build_raw: build_raw_l

build_raw_l: build_raw_o

	ld                                           \
	-o $(TARGET_RAW)                             \
	--dynamic-linker /lib64/ld-linux-x86-64.so.2 \
	main_raw.o                                   \
	function_raw.o                               \
	/usr/lib/x86_64-linux-gnu/Scrt1.o            \
	-lc

build_raw_o: build_raw_s
	as -o main_raw.o main_raw.s
	as -o function_raw.o function_raw.s

build_raw_s: build_raw_i
	gcc -S -o main_raw.s main_raw.i
	gcc -S -o function_raw.s function_raw.i

build_raw_i: 
	cpp -o main_raw.i main.c
	cpp -o function_raw.i function.c


# GCC build
build_gcc: build_gcc_l

build_gcc_l: build_gcc_o
	gcc -o $(TARGET_GCC) main_gcc.o function_gcc.o

build_gcc_o: build_gcc_s
	gcc -c -o main_gcc.o main_gcc.s
	gcc -c -o function_gcc.o function_gcc.s

build_gcc_s: build_gcc_i
	gcc -S -o main_gcc.s main_gcc.i
	gcc -S -o function_gcc.s function_gcc.i

build_gcc_i: 
	gcc -E -o main_gcc.i main.c
	gcc -E -o function_gcc.i function.c

# Run
run_raw:
	./$(TARGET_RAW)

run_gcc:
	./$(TARGET_GCC)

# Clean
clean_raw: 
	if [ -f $(TARGET_RAW) ]; then rm $(TARGET_RAW); fi
	if [ -f main_raw.o ]; then rm main_raw.o; fi
	if [ -f function_raw.o ]; then rm function_raw.o; fi
	if [ -f main_raw.s ]; then rm main_raw.s; fi
	if [ -f function_raw.s ]; then rm function_raw.s; fi
	if [ -f main_raw.i ]; then rm main_raw.i; fi
	if [ -f function_raw.i ]; then rm function_raw.i; fi

clean_gcc:
	if [ -f $(TARGET_GCC) ]; then rm $(TARGET_GCC); fi
	if [ -f main_gcc.o ]; then rm main_gcc.o; fi
	if [ -f function_gcc.o ]; then rm function_gcc.o; fi
	if [ -f main_gcc.s ]; then rm main_gcc.s; fi
	if [ -f function_gcc.s ]; then rm function_gcc.s; fi
	if [ -f main_gcc.i ]; then rm main_gcc.i; fi
	if [ -f function_gcc.i ]; then rm function_gcc.i; fi

	




	


