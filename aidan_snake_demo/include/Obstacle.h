#ifndef OBSTACLE
#define OBSTACLE
#include "raylib.h"
#include <string>
#include <cstdlib>
#include "globals.h"
#include <iostream>

class Obstacle{
private:
    int col, row; // Map coordinates 
public:
    Texture2D texture; // Textures for obstacles
    // Constructor
    Obstacle();
    // Draw texture to screen
    void Draw();
    // Returns whether inputted column and row are same as obstacle coordinates
    bool Collision(int,int);
    // Randomly changes map coordinates
    void Reset();
};

#endif
