#ifndef CONFIG
#define CONFIG
#include "raylib.h"
#include <string>
#include <cstdlib>

extern const int FPS; // frame rate
extern const int WIDTH; // windows creen width in pixels
extern const int HEIGHT; // window screen height in pixels
extern const char* NAME; // window name
extern const int CELL_SIZE; // size of each cell in pixels
extern const int ROWS; // number of cells in vertical direction
extern const int COLS; // number of cells in horizontal direction
extern const int CENTER_X; // x-center of map in pixels
extern const int CENTER_Y; // y-center of map in pixels
extern const int CELL_ORIGIN_X; // x-origin of cell map in pixels (left of map)
extern const int CELL_ORIGIN_Y; // y-origin of cell map in pixels (top of map)
extern const int NUM_WALLS; // total number of obstacles
enum DIR { UP, DOWN, LEFT, RIGHT }; // enumerated type for directions

// Returns cell x-position in pixels based on column input 
int GetCellX(int);
// Returns cell y-position in pixels based on row input
int GetCellY(int);

#endif