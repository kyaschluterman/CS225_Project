#include "raylib.h"
#include <vector>

/*
https://www.raylib.com/cheatsheet/cheatsheet.html

g++ testcode2.cc -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
*/

const int CELLSIZE = 20;
const int XGRIDSIZE = 60;
const int YGRIDSIZE = 36;

const int WINDOW_WIDTH = XGRIDSIZE * CELLSIZE;
const int WINDOW_HEIGHT = YGRIDSIZE * CELLSIZE;


struct RasterPos{ // useful way to store vectors I think
    int componentX;
    int componentY;
};

const RasterPos INITIAL_POSITION = {20,12};


class SnakeTest{ // the main player object for the game
private:
    RasterPos cell_position; // where the snake is 
    RasterPos cell_direction; // where the snake is heading 
public:
    SnakeTest(/* args */);
    ~SnakeTest();
    void move(); 
    bool collision();
    void updateDirection(int,int);
    void cellDraw();
    void reset();
};

SnakeTest::SnakeTest(){
    cell_position = INITIAL_POSITION; // starts the snake in the middle,
    cell_direction = {1,0};    // facing left
}

SnakeTest::~SnakeTest(){
}

void SnakeTest::move(){ // adds direction to the position, called every game iteration :)
    cell_position.componentX += cell_direction.componentX; 
    cell_position.componentY += cell_direction.componentY;
}

bool SnakeTest::collision(){ // checks if the snake is over the edges
    if(cell_position.componentX<=0 || cell_position.componentX>=XGRIDSIZE-1
        || cell_position.componentY<=0 || cell_position.componentY>=YGRIDSIZE-1){
            return true;
    }
    return false;
}

void SnakeTest::updateDirection(int x, int y){
    cell_direction = {x,y};
}

void SnakeTest::cellDraw(){
    DrawRectangle(cell_position.componentX * CELLSIZE,  cell_position.componentY * CELLSIZE,  CELLSIZE, CELLSIZE, BLACK);
}

void SnakeTest::reset(){
    cell_position = INITIAL_POSITION; // starts the snake in the middle,
    cell_direction = {1,0};    // facing left
}



int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib example - Snake test 2");
    SetTargetFPS(20);

    SnakeTest snake; // makes our player

    while (!WindowShouldClose()){

        if( !snake.collision() ){
            if( IsKeyPressed(KEY_UP)    ){ snake.updateDirection(0,-1); }
            if( IsKeyPressed(KEY_DOWN)  ){ snake.updateDirection(0,1); }
            if( IsKeyPressed(KEY_LEFT)  ){ snake.updateDirection(-1,0); }
            if( IsKeyPressed(KEY_RIGHT) ){ snake.updateDirection(1,0); }
            snake.move();
        }
        else if( IsKeyPressed(KEY_R) ){
            snake.reset();
        }
        else{
            DrawText("Game Over, press r to restart :)", WINDOW_WIDTH/3, WINDOW_HEIGHT/2, 25, DARKGRAY);
        }


        BeginDrawing();

        ClearBackground(BEIGE);
        
        snake.cellDraw(); // this is easier than making getter functions and doing it that way.
        
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}





// Toolbox:

// DrawRectangle(cell_position.componentX * CELLSIZE,  cell_position.componentY * CELLSIZE,  CELLSIZE, CELLSIZE, BLACK);
//ClearBackground(BEIGE);
//DrawText("Congrats! You created your first window!", WINDOW_WIDTH/4, WINDOW_HEIGHT/2, 20, DARKGRAY);