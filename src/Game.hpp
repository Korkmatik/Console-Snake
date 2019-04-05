#include <ncurses.h>

#include "Snake.hpp"

class Game
{
    public:
        // Constructor takes width and height of the playfield
        Game();

        // initializes the game, like created food and the snake
        // returns true if initialization succeded
        bool initializeGame(int width, int heigth);

        // Starts the Game
        void start();

    private:
        // to store the information if the game was initialized
        bool isGameInitialized;
        // determines wether the game ends
        bool isGameOver;
        // stores the user input
        int userInput;

        // Stores width and height of the playfield
        Vector2* playfieldDimensions;

        // The snake(player) of the game
        Snake* snake;

        //initializes the ncurses library
        void initializeNCurses();


        // Handles user input during the game
        void handleUserInput();
        // implements all the game logic
        void gameLogic();
        // prints the game on the screen
        void renderGame();

};