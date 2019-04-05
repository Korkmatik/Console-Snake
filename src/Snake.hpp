#include <vector>

#include "Vector2.hpp"

class Snake 
{
	public:
		// Moving directions of the snake
		enum DIRECTIONS { TOP, LEFT, BOTTOM, RIGHT };

		// Positions the head of the snake at $pos and the tail underneath
		// Initial size of the snake is 5
		// Sets initial moving direction to top
		Snake(Vector2 pos);

		// returns head symbol of the snake
		char getSymbolHead() const;
		// return tail symbol of the snake
		char getSymbolTail() const;
		
		// returns the current score of the snake
		unsigned getScore() const;
		// Makes the snake larger and adds score another point to the scores after eating a food
		unsigned addPoint();

		// Returns all positions of the snake parts
		const std::vector<Vector2>& getPositions() const;

		// moves the snake to the current direction
		// returns new position of the head
		const Vector2& move();
	private:
		char symbol_head, symbol_tail; // stores the symbol of the Snake head and the snake tail which should be printed in the console
		unsigned int score; // stores the snake's score
		 
		std::vector<Vector2> positions;	// stores the positions of the body parts

		DIRECTIONS movingDirection; // stores the current moving direction of the snake

};
