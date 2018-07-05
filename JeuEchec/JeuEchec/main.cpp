#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"

int main(int argc, char* args[]) {
	Game* game = new Game();
	game->Run();
	delete game;
	return 0;
}