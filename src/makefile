CC = g++ -std=c++17

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

GAME = main.cpp

SERVER = server.cpp

AUX = game.cpp TextureManager.cpp GameObject.cpp Map.cpp Menu.cpp Enemy.cpp Spawnable.cpp

GAME_NAME = mygame
SERVER_NAME = myserver

all: $(GAME) $(AUX)
	$(CC) $(GAME) $(AUX) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(GAME_NAME)

server: $(SERVER)
	$(CC) $(SERVER) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(SERVER_NAME)

clean:
	rm mygame
	rm -f *.o 