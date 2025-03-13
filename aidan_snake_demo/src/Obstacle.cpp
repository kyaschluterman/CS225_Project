#include "Obstacle.h"
using namespace std;

Obstacle::Obstacle() {
    col = rand() % COLS + 1;
    row = rand() % ROWS + 1;
    texture = LoadTexture("snake.png");
}

void Obstacle::Reset() {
    col = rand() % COLS + 1;
    row = rand() % ROWS + 1;
}

bool Obstacle::Collision(int c, int r) {
    if (c == col && r == row) {
        return true;
    }
    return false;
}

void  Obstacle::Draw() {
    DrawTexture(texture, GetCellX(col), GetCellY(row), WHITE);
}
