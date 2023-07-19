all: build

build:
	gcc -Wall -Wextra -Werror -m32 -o example_a example_a.c misc.c
	gcc -Wall -Wextra -Werror -m32 -o example_b example_b.c misc.c
	gcc -Wall -Wextra -Werror -m32 -o example_b_child example_b_child.c
	gcc -Wall -Wextra -Werror -m32 -o example_c example_c.c misc.c
	gcc -Wall -Wextra -Werror -m32 -o example_c_child example_c_child.c
	gcc -Wall -Wextra -Werror -m32 -o example_d example_d.c misc.c
	gcc -Wall -Wextra -Werror -m32 -o example_d_child example_d_child.c
	gcc -Wall -Wextra -Werror -m32 -o example_e example_e.c misc.c
	gcc -Wall -Wextra -Werror -m32 -o example_e_child example_e_child.c
	gcc -Wall -Wextra -Werror -m32 -o test_debug test_debug.c

clean:
	rm -rf example_a
	rm -rf example_b
	rm -rf example_b_child
	rm -rf example_c
	rm -rf example_c_child
	rm -rf example_d
	rm -rf example_d_child
	rm -rf example_e
	rm -rf example_e_child
	rm -rf test_debug
