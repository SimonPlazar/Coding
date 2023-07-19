all: build

build:
	gcc -msse4.2 -O2 -o spo_simd_o2 spo_simd.c spo_simd.h
	gcc -msse4.2 -o spo_simd spo_simd.c spo_simd.h

run:
	./spo_simd
	./spo_simd_o2

clean:
	if [ -f main ]; then rm spo_simd; fi
