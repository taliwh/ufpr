CC = gcc-14
CFLAGS = -Wall -Wextra -Werror -g -std=c23
MAIN = prova1_20256088
OBJ = main.o arvoreB.o fila.o
HDR = arvoreB.h fila.h

$(MAIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJ)

main.o: main.c $(HDR)
	$(CC) $(CFLAGS) -c main.c

arvoreB.o: arvoreB.c arvoreB.h 
	$(CC) $(CFLAGS) -c arvoreB.c

fila.o: fila.c fila.h
	$(CC) $(CFLAGS) -c fila.c

run: $(MAIN)
	./$(MAIN)

valgrind: $(MAIN)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN)

clean:
	rm -f *~ *.o $(MAIN) $(MAIN).tar.gz
