# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
SRC_DIR := ./src
EXEC_DIR := ./exec

# Find all Bash scripts
BASH_SCRIPTS := $(shell find $(SRC_DIR) -name "*.sh")

BASH_TARGETS := $(patsubst $(SRC_DIR)/%.sh,$(EXEC_DIR)/%,$(BASH_SCRIPTS))

all: $(BASH_TARGETS)

# "Build" step for bash scripts
$(EXEC_DIR)/%: src/%.sh
	mkdir -p $(dir $@)
	cp $< $@
	chmod u+x $@

.PHONY: clean	
clean:
	if [ -d $(EXEC_DIR) ]; then rm -r "$(EXEC_DIR)"; fi
