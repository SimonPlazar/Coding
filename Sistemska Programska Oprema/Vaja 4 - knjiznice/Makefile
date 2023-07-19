TARGET_STATIC = "prog_static"
TARGET_DYNAMIC_IMP = "prog_dyn_imp"
TARGET_DYNAMIC_EXP = "prog_dyn_exp"

all: build run

build: build_static build_dyn_imp build_dyn_exp

run: run_static run_dyn_imp run_dyn_exp

clean:
	if [ -f $(TARGET_STATIC) ]; then rm $(TARGET_STATIC); fi
	if [ -f add.o ]; then rm -f add.o; fi
	if [ -f mul.o ]; then rm -f mul.o; fi
	if [ -f libmath.a ]; then rm libmath.a; fi
	if [ -f $(TARGET_DYNAMIC_IMP) ]; then rm $(TARGET_DYNAMIC_IMP); fi
	if [ -f libmath.so.2.4 ]; then rm libmath.so.2.4; fi
	rm -f libmath.so.2
	rm -f libmath.so
	if [ -f $(TARGET_DYNAMIC_EXP) ]; then rm $(TARGET_DYNAMIC_EXP); fi


build_static:
	gcc -c -o add.o add.c
	gcc -c -o mul.o mul.c
	ar crs libmath.a add.o mul.o
	gcc -o $(TARGET_STATIC) main.c libmath.a

build_dyn_imp:
	gcc -c -fPIC -o add.o add.c
	gcc -c -fPIC -o mul.o mul.c
	gcc -shared -o libmath.so.2.4 -Wl,-soname,libmath.so.2 add.o mul.o
	ln -sf libmath.so.2.4 libmath.so.2
	ln -sf libmath.so.2 libmath.so
	gcc -o $(TARGET_DYNAMIC_IMP) main.c -L. -lmath

build_dyn_exp:
	gcc -c -fPIC -o add.o add.c
	gcc -c -fPIC -o mul.o mul.c
	gcc -shared -o libmath.so.2.4 -Wl,-soname,libmath.so.2 add.o mul.o
	ln -sf libmath.so.2.4 libmath.so.2
	ln -sf libmath.so.2 libmath.so
	gcc -o $(TARGET_DYNAMIC_EXP) main_exp.c -ldl

run_static:
	./$(TARGET_STATIC)

run_dyn_imp:
	LD_LIBRARY_PATH=. ./prog_dyn_imp

run_dyn_exp:
	./$(TARGET_DYNAMIC_EXP)