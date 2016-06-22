game: 	deck.o game.o
	gcc -o game -g deck.o game.o

deck.o:	deck.h deck.c
	gcc -c -g deck.c

game.o:	game.c deck.h
	gcc -c -g game.c

clean:
	rm -rf game.o deck.o game
