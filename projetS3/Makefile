SRC=main.c fonction.c fonctions_fichiers.c
BIN=Jeu

$(BIN): $(SRC)
	gcc -Wall -g -std=c99 $(SRC) `sdl-config --cflags --libs` -o $(BIN) -lm

clean:
	rm -f $(BIN)
