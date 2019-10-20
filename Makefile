SRC = *.c

FILES = $(addprefix src/, $(SRC))

all:
	gcc -g -Iinclude -Wall -Werror -Wextra -fsanitize=address $(FILES)

# test:
# 	gcc -g -Iinclude -Wall -Werror -Wextra -fsanitize=address 