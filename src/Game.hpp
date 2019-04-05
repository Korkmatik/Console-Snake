#include "Snake.hpp"

class Game
{
    public:
        // Constructor takes width and height of the playfield
        Game(int width, int heigth);

        // Starts the Game
        void start();

    private:
        // Stores width and height of the playfield
        Vector2 playfieldDimensions;

        Snake* snake;



}