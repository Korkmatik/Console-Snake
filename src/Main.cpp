#include <iostream>

#include "Snake.hpp"

void print(const std::vector<Vector2>& pos)
{
	for(int i=0; i<pos.size(); i++) {
		std::cout << "Pos #" << i << " (" << pos[i].x << "/" << pos[i].y << ")\n";
	}
}

int main()
{
	Snake s(Vector2(5, 5));

	auto pos = s.getPositions();
	
	print(pos);

	std::cout << "head-symbol: " << s.getSymbolHead() << " --tail-symbol" << s.getSymbolTail() << std::endl;
	
	s.move();
	
	pos = s.getPositions();

	print(pos);
	
	s.addPoint();

	pos = s.getPositions();

	print(pos);

	return 0;
}
