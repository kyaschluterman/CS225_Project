#pragma once
#include "raylib.h"
#include <string>
#include <cstdlib>
#include "config.h"
#include <iostream>

using namespace std;



class Obstacle{
private:
    
    int col, row;
public:
    Texture2D texture;
    Obstacle();
    void Draw();
    bool Collision(int,int);
};

Obstacle::Obstacle(){

    col = rand()%COLS + 1;
    row = rand()%ROWS + 1;
    texture = LoadTexture("snake.png");
}

bool Obstacle::Collision(int c, int r){
    if(c==col && r==row){
        return true;
    }
    return false;
}

void  Obstacle::Draw(){
    DrawTexture(texture, GetCellX(col), GetCellY(row), WHITE);
}


struct teststruct{
    int a;
};
