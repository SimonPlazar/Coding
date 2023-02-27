# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
SRC_DIR := ./src
EXEC_DIR := ./exec

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
BASH_SCRIPTS := $(shell find $(SRC_DIR) -name '*.sh')

# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
BASH_TARGETS := $(patsubst $(SRC_DIR)/%.sh,$(EXEC_DIR)/%,$(BASH_SCRIPTS))

all: $(BASH_TARGETS)

# "Build" step for bash scripts
$(EXEC_DIR)/%: src/%.sh
	mkdir -p $(dir $@)
	cp $< $@
	chmod u+x $@
	
clean:
	rm -rf exec/
