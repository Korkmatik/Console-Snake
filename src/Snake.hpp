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

		/* snake symbol */
		// returns head symbol of the snake
		char getSymbolHead() const;
		// return tail symbol of the snake
		char getSymbolTail() const;
		
		/* snake score */
		// returns the current score of the snake
		unsigned getScore() const;
		// Makes the snake larger and adds another point to the score after eating a food
		unsigned addPoint();

		// Returns all positions of the snake parts
		const std::vector<Vector2>& getPositions() const;

		/* snake movement */
		// moves the snake to the current direction
		// returns new position of the head
		const Vector2& move();
		// sets the new directions in which the snake should move
		void setDirection(DIRECTIONS newDirection);

		/* collision detection */
		bool isTouchingItself();

	private:
		char symbol_head, symbol_tail; // stores the symbol of the Snake head and the snake tail which should be printed in the console
		unsigned int score; // stores the snake's score
		 
		std::vector<Vector2> positions;	// stores the positions of the body parts

		DIRECTIONS movingDirection; // stores the current moving direction of the snake

};
