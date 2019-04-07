#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "Game.hpp"

Game::Game()
{
    // initializing srand for the food object
    srand(time(NULL));

    isGameInitialized = false;

    playfieldDimensions = nullptr;
    snake = nullptr;
    food = nullptr;
}

Game::~Game()
{
    if (playfieldDimensions != nullptr)
        delete playfieldDimensions;
        
    if (snake != nullptr)
        delete snake;

    if (food != nullptr)
        delete food;

    endwin();
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

    // Initializing the food
    food = new Food(*playfieldDimensions);
    if (food == nullptr) {
        return false;
    }

    // placing the food on the playfield
    foodPosition = food->spawnFood(snake);

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
        usleep(2000000/FPS);
    }
}

void Game::initializeNCurses()
{
    // allocate memory for ncurses
    initscr();
    // activating ability to use colors if the console can display them
    if (hasColor = has_colors())
        initializeColors();
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

void Game::initializeColors()
{   
    start_color();

    // Color of the food
    init_pair(C_FOOD, COLOR_YELLOW, COLOR_BLACK);
    // Color of the snake
    init_pair(C_SNAKE, COLOR_GREEN, COLOR_BLACK);
    // Color of the walls of the playfield
    init_pair(C_WALL, COLOR_WHITE, COLOR_WHITE);
    // Color of the title in the UI Elements
    init_pair(C_TITLE, COLOR_CYAN, COLOR_BLACK);
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
            endGame();
            break;

        // movement
        case MOVE_UP:
        case KEY_UP:
            snake->setDirection(Snake::DIRECTIONS::TOP);
            break;
    
        case MOVE_DOWN:
        case KEY_DOWN:
            snake->setDirection(Snake::DIRECTIONS::BOTTOM);
            break;
        
        case MOVE_LEFT:
        case KEY_LEFT:
            snake->setDirection(Snake::DIRECTIONS::LEFT);
            break;

        case MOVE_RIGHT:
        case KEY_RIGHT:
            snake->setDirection(Snake::DIRECTIONS::RIGHT);
            break;

        default:
            break;
    }

    checkForCollisions();

    snake->move();
}

void Game::renderGame()
{
    // Clearing the screen
    erase();

    /* insert the game objects which shall be printed here */
    
    printFood();
    printSnake();
    printPlayfield();
    printUI();

    // prints on the ncurses screen
    refresh();
}

void Game::printSnake()
{
    // getting all current positions of the snake
    auto snakePos = snake->getPositions();

    // getting the character which represents the snake tail
    char snakeTail = snake->getSymbolTail();

    // setting the color of the snake if console can output it
    if (hasColor)
        attron(COLOR_PAIR(C_SNAKE));

    // printing the head of the snake on the console
    mvprintw(snakePos[0].y, snakePos[0].x, "%c", snake->getSymbolHead());

    // printing the tail of the snake on the console
    for(int i = 1; i < snakePos.size(); i++)
    {
        mvprintw(snakePos[i].y, snakePos[i].x, "%c", snakeTail);
    }

    // disabling snake color 
    if (hasColor)
        attroff(COLOR_PAIR(C_SNAKE));
}

void Game::printPlayfield()
{
    if(hasColor)
        attron(COLOR_PAIR(C_WALL));

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

    if (hasColor)
        attroff(COLOR_PAIR(C_WALL));
}

void Game::printFood()
{
    if (hasColor)
        attron(COLOR_PAIR(C_FOOD));
    mvprintw(foodPosition.y, foodPosition.x, "%c", food->getFoodSymbol());
    if (hasColor)
        attroff(COLOR_PAIR(C_FOOD));
}

void Game::printUI()
{
    // initial x positions of the ui elements 
    int offset = playfieldDimensions->x + 5;
    // initial y position of the ui
    int y = 0;
    // index variable for loops
    int i = 0;

    // activate color for the title
    if(hasColor)
        attron(COLOR_PAIR(C_TITLE));

    // prints the title of the game right to the playfield
    for (; i < SNAKE_TITLE.size(); y++, i++) {
        mvprintw(y, offset, "%s", SNAKE_TITLE[i]);
    }
    
    // prints a line underneath the title
    y += 1;
    for(i=0; i < strlen(SNAKE_TITLE[0]); i++) {
        mvprintw(y, offset + i, "#");
    }

    if(hasColor)
        attroff(COLOR_PAIR(C_TITLE));

    // computes the position where the stats should be printed 
    y = SNAKE_TITLE.size() + 3;

    // print the score of the snake
    mvprintw(y++, offset, "Score: %d", snake->getScore());
}

void Game::endGame()
{
    isGameOver = true;
}

void Game::checkForCollisions()
{
    if(snake->isTouchingItself() || isSnakeTouchingWall())
        endGame();
    else if(food->isTouchingSnake(snake))
        snakeIsTouchingFoodEvent();
}

bool Game::isSnakeTouchingWall()
{
    bool snakeIsTouching = false;

    Vector2 snakeHeadPos = snake->getPositions()[0];

    
    if (
        snakeHeadPos.x <= 0 || // snake is touching the left wall
        snakeHeadPos.x >= playfieldDimensions->x || // snake is touching right wall
        snakeHeadPos.y <= 0 || // snake is touching top wall
        snakeHeadPos.y >= playfieldDimensions->y // snake is touching bottom wall
        )
        snakeIsTouching = true;


    return snakeIsTouching;        
}

void Game::snakeIsTouchingFoodEvent()
{
    snake->addPoint();
    foodPosition = food->spawnFood(snake);
}