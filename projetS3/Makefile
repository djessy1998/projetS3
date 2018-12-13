SRC=creator.c main.c collisions.c fonctions_fichiers.c input.c fonctions_tab.c listes.c deplacement.c traitement_input.c affichage.c vie.c perlin.c generator.c minage.c construction.c deplacement_monstre.c combat.c destructor.c atlas.c fondMusique.c
BIN=Jeu

$(BIN): $(SRC)
	gcc -Wall -g -std=c99 $(SRC) `sdl-config --cflags --libs` -lSDL_mixer -L./usr/lib -I./usr/include -lSDL_ttf -o $(BIN) -lm

clean:
	rm -f $(BIN)
