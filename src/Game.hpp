#include <ncurses.h>

#include "Snake.hpp"

class Game
{
    public:
        // Constructor takes width and height of the playfield
        Game();

        // initializes the game, like created food and the snake
        // returns true if initialization succeded
        bool initializeGame(int width=100, int heigth=30);

        // Starts the Game
        void start(unsigned FPS=30);

    private:
        // to store the information if the game was initialized
        bool isGameInitialized;
        // determines wether the game ends
        bool isGameOver;
        // stores the user input
        int userInput;
        // stores the controls
        enum CONTROLS_TYPE  {   QUIT='q', // Game functionality
                                MOVE_UP='w', MOVE_DOWN='s', MOVE_LEFT='a', MOVE_RIGHT='d' // movement
                            };

        // Stores width and height of the playfield
        Vector2* playfieldDimensions;
        // The snake(player) of the game
        Snake* snake;


        /* initializer functions */
        // initializes the ncurses library
        void initializeNCurses();


        /* main game loop */
        // Handles user input during the game
        void handleUserInput();
        // implements all the game logic
        void gameLogic();
        // prints the game on the screen
        void renderGame();


        /* functions that print the game objects on the console */
        // prints the snake on the console
        void printSnake();
        // prints the playfield on the console
        void printPlayfield();
};