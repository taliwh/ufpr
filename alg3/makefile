

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=c23
LDLIBS = -lm
MAIN = ?



run: $(MAIN)
	./$(MAIN)


valgrind: $(MAIN)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN)


tgz: clean
