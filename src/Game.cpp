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
        usleep(1750000/FPS);
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
    // disable cursor
    curs_set(false);
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
        case QUIT:
            isGameOver = true;
            endwin();
            break;

        // movement
        case MOVE_UP:
            snake->setDirection(Snake::DIRECTIONS::TOP);
            break;
    
        case MOVE_DOWN:
            snake->setDirection(Snake::DIRECTIONS::BOTTOM);
            break;
        
        case MOVE_LEFT:
            snake->setDirection(Snake::DIRECTIONS::LEFT);
            break;

        case MOVE_RIGHT:
            snake->setDirection(Snake::DIRECTIONS::RIGHT);
            break;

        default:
            break;
    }

    snake->move();
}

void Game::renderGame()
{
    // Clearing the screen
    erase();

    /* insert the game objects which shall be printed here */
    
    printSnake();
    printPlayfield();

    // prints on the ncurses screen
    refresh();
}

void Game::printSnake()
{
    // getting all current positions of the snake
    auto snakePos = snake->getPositions();

    // getting the character which represents the snake tail
    char snakeTail = snake->getSymbolTail();

    // printing the head of the snake on the console
    mvprintw(snakePos[0].y, snakePos[0].x, "%c", snake->getSymbolHead());

    // printing the tail of the snake on the console
    for(int i = 1; i < snakePos.size(); i++)
    {
        mvprintw(snakePos[i].y, snakePos[i].x, "%c", snakeTail);
    }
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