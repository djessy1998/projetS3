SRC=main.c fonction.c fonctions_fichiers.c input.c fonctions_tab.c listes.c deplacement.c traitement_input.c
BIN=Jeu

$(BIN): $(SRC)
	gcc -Wall -g -std=c99 $(SRC) `sdl-config --cflags --libs` -lSDL_ttf -o $(BIN) -lm

clean:
	rm -f $(BIN)
