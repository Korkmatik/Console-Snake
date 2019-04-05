#include <iostream>

#include "Game.hpp"

int main()
{
	Game snakeGame{};

	if(snakeGame.initializeGame())
		snakeGame.start();

	return 0;
}
