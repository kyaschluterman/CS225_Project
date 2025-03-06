#pragma once
#include "raylib.h"
#include <string>
#include <cstdlib>
#include "config.h"

#include <iostream>

class Obstacle{
private:
    Texture2D texture;
    int col, row;
public:
    Obstacle();
    void Draw();
    bool Collision(int,int);
};

Obstacle::Obstacle(){
    srand(time(0));
    col = rand()%COLS;
    row = rand()%ROWS;
    texture = LoadTexture("snake.png");
}

bool Obstacle::Collision(int x, int y){
    if(x==col && y==row){
        return true;
    }
    return false;
}

void  Obstacle::Draw(){
    int cell_x = col * CELL_SIZE + CELL_ORIGIN_X;
    int cell_y = row * CELL_SIZE + CELL_ORIGIN_Y;
    DrawTexture(texture, cell_x, cell_y, WHITE);

}



