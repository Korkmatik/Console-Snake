#include "Snake.hpp"

Snake::Snake(Vector2 pos) : symbol_head('O'), symbol_tail('o'), score(0)
{
	if (pos.x < 0)
		pos.x = 0;
	if (pos.y < 0)
		pos.y = 0;

	// positioning the head at the initial position 
	this->positions.push_back(pos);

	// positioning 4 tail parts
	for (int i=0; i < 4; i++) {
		pos.y += 1;
		this->positions.push_back(pos);
	}

	// setting initial moving direction to top
	movingDirection = TOP;
}

char Snake::getSymbolHead() const
{
	return symbol_head;
}

char Snake::getSymbolTail() const
{
	return symbol_tail;
}

unsigned Snake::getScore() const
{
	return this->score;
}

unsigned Snake::addPoint()
{

	score += 1;
	Vector2 lastPos = positions.back();
	
	// determining where the snake is moving
	switch (movingDirection) {
		case TOP:
			lastPos.y += 1;
			break;
		case LEFT:	
			lastPos.x += 1;
			break;
		case BOTTOM:
			lastPos.y -= 1;
			break;
		case RIGHT:
			lastPos.x -= 1;
			break;
	}

	// adding the new tail part
	positions.push_back(lastPos);

	return score;
}

const std::vector<Vector2>& Snake::getPositions() const
{
	return positions;
}

const Vector2& Snake::move()
{	
	// getting the position of the head
	Vector2 prev = *(positions.begin());
	Vector2 newPos = prev;
	Vector2 tmp(0, 0);

	int newX = 0;
	int newY = 0;

	// determining in which direction the snake is moving
	switch (movingDirection) {
		case TOP:
			newY = -1;
			break;
		case LEFT:
			newX = -1;
			break;
		case BOTTOM:
			newY = 1;
			break;
		case RIGHT:
			newX = 1;
			break;
	}

	// setting the head's new position
	newPos.x += newX;
	newPos.y += newY;

	positions[0] = newPos;
	
	// moving every tail part
	for (int i=1; i < positions.size(); i++) {
		tmp = positions[i];
		positions[i] = prev;
		prev = tmp;
	}

	return positions[0];
}
