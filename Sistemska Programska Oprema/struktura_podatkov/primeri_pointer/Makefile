TARGET_ST = structures
TARGET_ST_32 = structures_32
TARGET_PO = pointers
TARGET_BI = bits
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -Wpedantic

all: build run

build:
	@echo "BUILD"
	@echo "====="
	$(CC) $(CFLAGS) -o $(TARGET_ST) structures.c
	$(CC) $(CFLAGS) -m32 -Wno-format -o $(TARGET_ST_32) structures.c
	$(CC) $(CFLAGS) -o $(TARGET_PO) pointers.c
	$(CC) $(CFLAGS) -o $(TARGET_BI) bits.c

run:
	@echo
	@echo "RUN structures"
	@echo "=============="
	@./$(TARGET_ST)

	@echo
	@echo "RUN structures_32"
	@echo "================="
	@./$(TARGET_ST_32)

	@echo
	@echo "RUN pointers"
	@echo "============"
	@./$(TARGET_PO)

	@echo
	@echo "RUN bits"
	@echo "========"
	@./$(TARGET_BI)

clean:
	if [ -f $(TARGET_ST) ]; then rm $(TARGET_ST); fi
	if [ -f $(TARGET_ST_32) ]; then rm $(TARGET_ST_32); fi
	if [ -f $(TARGET_PO) ]; then rm $(TARGET_PO); fi
	if [ -f $(TARGET_BI) ]; then rm $(TARGET_BI); fi
