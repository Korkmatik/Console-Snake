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

void Game::start()
{
    if(!isGameInitialized)
        return;

    while(!isGameOver) {
        renderGame();
        handleUserInput();
        gameLogic();
    }
}

void Game::initializeNCurses()
{
    // allocate memory for ncurses
    initscr();
    // activate function keys and arrow keys
    keypad(stdscr, TRUE);
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
    // displaying user input on the screen
    printw("you pressed: %c", userInput);
}

void Game::renderGame()
{
    // prints on the ncurses screen
    refresh();
}
