#include <iostream>

#include "Game.hpp"

void print(const std::vector<Vector2>& pos)
{
	for(int i=0; i<pos.size(); i++) {
		std::cout << "Pos #" << i << " (" << pos[i].x << "/" << pos[i].y << ")\n";
	}
}

int main()
{
	Game snakeGame{};

	if(snakeGame.initializeGame(80, 50))
		snakeGame.start();

	return 0;
}
