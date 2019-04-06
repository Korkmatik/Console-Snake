 #include <cstdlib>
 
 #include "Food.hpp"

 Food::Food(Vector2 screenDimensions)
 {
     this->screenDimensions = screenDimensions;

     symbol = '*';
 }

 const Vector2& Food::spawnFood(const class Snake* const snake)
 {  
     // stores the new x and y positions of the food
     int randXPos = 0;
     int randYPos = 0;

     // position the food
     while (true) {
         // food should be inside the playfield 
         randXPos = (rand() % (screenDimensions.x - 2)) + 1;
         randYPos = (rand() % (screenDimensions.y - 2)) + 1;

        // checking if the food would already intersect with the snake
         auto snakePositions = snake->getPositions();
         for(int i = 0; i < snakePositions.size(); i++) {
             // if the food already intersects with the snake -> calculate a new position
            if (snakePositions[i].x == randXPos && snakePositions[i].y == randYPos)
                continue;
         }

        // food doesn't intersect with borders and snake
         break;
     }

    // the food's new Position
    position = Vector2(randXPos, randYPos);

    return position;
 }

char Food::getFoodSymbol() const
{
    return symbol;
}

bool Food::isTouchingSnake(const class Snake* const snake)
{
    // getting the position of the snake's head
    Vector2 snakeHead = snake->getPositions()[0];

    // if the head of the snake touches the food
    if (snakeHead.x == position.x && snakeHead.y == position.y) {
        return true;
    }

    // the food isn't being touched by the snake's heads
    return false;
}

const Vector2& Food::getPosition() const
{
    return position;
}