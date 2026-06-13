CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -std=c99

MAIN = catland
ENTREGA = A3_GRR20256088_THALISIA

ALLEGRO_FLAGS = $(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_audio-5 allegro_acodec-5 allegro_primitives-5 --libs --cflags)

HDR = game.h cat.h land.h creatures.h joystick.h states.h camera.h physics.h save.h

OBJ = game.o cat.o land.o creatures.o joystick.o states.o camera.o physics.o save.o

$(MAIN): main.o $(OBJ)
	$(CC) main.o $(OBJ) -o $(MAIN) $(ALLEGRO_FLAGS)

main.o: main.c $(HDR)

game.o: game.c game.h
cat.o: cat.c cat.h
land.o: land.c land.h
creatures.o: creatures.c creatures.h
joystick.o: joystick.c joystick.h
states.o: states.c states.h
camera.o: camera.c camera.h
physics.o: physics.c physics.h
save.o: save.c save.h

run: $(MAIN)
	./$(MAIN)

valgrind: $(MAIN)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(MAIN)

tgz: clean
	-mkdir -p /tmp/$(USER)/$(ENTREGA)
	chmod 0700 /tmp/$(USER)/$(ENTREGA)
	cp *.c *.h Makefile /tmp/$(USER)/$(ENTREGA)
	cp -r assets /tmp/$(USER)/$(ENTREGA)
	tar czvf $(ENTREGA).tgz -C /tmp/$(USER) $(ENTREGA)
	rm -rf /tmp/$(USER)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

clean:
	rm -f *~ *.o $(MAIN) $(ENTREGA).tgz save.cat