#include <unistd.h>

#include "Game.hpp"

Game::Game()
{
    isGameInitialized = false;

    playfieldDimensions = nullptr;
    snake = nullptr;
}

bool Game::initializeGame(int width, int heigth)
{
    // Initializing playfield dimension
    playfieldDimensions = new Vector2(width, heigth);

    // Initializing the snake
    snake = new Snake(Vector2(width/2, heigth/2));

    // checking if any memory allocation failed
    if (playfieldDimensions == nullptr ||
        snake == nullptr) 
    {
        return false;
    }

    isGameOver = false;

    initializeNCurses();

    isGameInitialized = true;
    return isGameInitialized;
}

void Game::start(unsigned FPS)
{
    // start the game only if it is initialized
    if(!isGameInitialized)
        return;

    // main game loop
    while(!isGameOver) {
        renderGame();
        handleUserInput();
        gameLogic();

        // setting FPS
        usleep(1000/FPS);
    }
}

void Game::initializeNCurses()
{
    // allocate memory for ncurses
    initscr();
    // don't wait until the user actually inputs anything
    nodelay(stdscr, true);
    // activate function keys and arrow keys
    keypad(stdscr, true);
    // don't store any input in a buffer
    cbreak();
    // don't print user input on screen
    noecho();
}

void Game::handleUserInput()
{
    // Getting user input
    userInput = getch();
}

void Game::gameLogic()
{
    switch (userInput)
    {
        // quit the game
        case 'q':
            isGameOver = true;
            endwin();
            break;
    
        default:
            break;
    }
}

void Game::renderGame()
{
    // Clearing the screen
    //erase();

    /* insert here the game objects which shall be printed */
    
    printPlayfield();

    // prints on the ncurses screen
    refresh();
}

void Game::printPlayfield()
{
    // Top row of the playfield
    for(int x = 0; x < playfieldDimensions->x; x++)
    {
        mvprintw(0, x, "#");
    }
    
    // Bottom row of the playfield
    for(int x = 0; x < playfieldDimensions->x; x++)
    {
        mvprintw(playfieldDimensions->y, x, "#");
    }

    // Left side of the playfield
    for(int y = 1; y < playfieldDimensions->y; y++)
    {
        mvprintw(y, 0, "#");
    }
    
    // Right side of the playfield
    for(int y = 1; y < playfieldDimensions->y; y++)
    {
        mvprintw(y, playfieldDimensions->x-1, "#");
    }
    
}