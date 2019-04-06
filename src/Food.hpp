#ifndef FOOD_H
#define FOOD_H

#include "Vector2.hpp"
#include "Snake.hpp"

class Food
{
    public:
        // To generate a food object, the food object needs to know the playfield size
        Food(Vector2 screenDimensions);

        // calculates a random position for the food in the playfield
        // returns the new position
        const Vector2& spawnFood(const class Snake* const snake);

        // return the food symbol which should be printed
        char getFoodSymbol() const;

        // checks if a snake touches the food
        bool isTouchingSnake(const class Snake* const snake);

        // returns the current position of the food
        const Vector2& getPosition() const;

    private:
        // stores playfield dimensions
        Vector2 screenDimensions;

        // the symbol of the food
        char symbol;
        // stores the food's position on the playfield
        Vector2 position;
};

#endif