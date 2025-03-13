#ifndef OBSTACLE
#define OBSTACLE
#include "raylib.h"
#include <string>
#include <cstdlib>
#include "globals.h"
#include <iostream>

class Obstacle{
private:
    
    int col, row;
public:
    Texture2D texture;
    Obstacle();
    void Draw();
    bool Collision(int,int);
    void Reset();
};

#endif
