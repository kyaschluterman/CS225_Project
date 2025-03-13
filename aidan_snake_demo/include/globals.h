#ifndef CONFIG
#define CONFIG
#include "raylib.h"
#include <string>
#include <cstdlib>

extern const int FPS;
extern const int WIDTH;
extern const int HEIGHT;
extern const char* NAME;
extern const int CELL_SIZE;
extern const int ROWS;
extern const int COLS;
extern const int CENTER_X;
extern const int CENTER_Y;
extern const int CELL_ORIGIN_X;
extern const int CELL_ORIGIN_Y;
extern const int MAX_FRUIT;
extern const int NUM_WALLS;
enum DIR { UP, DOWN, LEFT, RIGHT };

int GetCellX(int);
int GetCellY(int);

#endif