#include "Game.h"


int main(int argc, char ** argv) {
	Game game("Extended Game Engine", 700, 700,true,60,false);

	try {
		game.run();
	}
	catch (std::exception e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	return 0;
}