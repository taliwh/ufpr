
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=c23
MAIN = prova1_20256088
# OBJ = possiveis arquivos objetos
HDR = arvoreB.h



$(MAIN): $(MAIN).o # $(OBJ)

$(MAIN).o: $(MAIN).c $(HDR)

run: $(MAIN)
	./$(MAIN)


valgrind: $(MAIN)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN)


tgz: clean	
	-mkdir -p /tmp/$(USER)/$(MAIN)
	chmod 0700 /tmp/$(USER)/$(MAIN)
	cp *.c *.h makefile /tmp/$(USER)/$(MAIN)
	tar czvf $(MAIN).tar.gz -C /tmp/$(USER) $(MAIN)
	rm -rf /tmp/$(USER)


clean:
	rm -f *~ *.o $(MAIN) $(MAIN).tar.gz
