#pragma once
#include "raylib.h"
#include <string>
#include <cstdlib>

const int FPS = 60;
const int WIDTH = 1000;
const int HEIGHT = 1000;
const char* NAME = "Snake";
const int CELL_SIZE = 16;
const int ROWS = 40;
const int COLS = 40;
const int CENTER_X = WIDTH / 2;
const int CENTER_Y = HEIGHT / 2;
const int CELL_ORIGIN_X = CENTER_X - COLS * CELL_SIZE / 2;
const int CELL_ORIGIN_Y = CENTER_Y - ROWS * CELL_SIZE / 2;
const int MAX_FRUIT = ROWS * COLS;
const int NUM_WALLS = 15;
enum DIR {UP, DOWN, LEFT, RIGHT};

int GetCellX(int col) {
	return col * CELL_SIZE + CELL_ORIGIN_X;
}

int GetCellY(int row) {
	return row * CELL_SIZE + CELL_ORIGIN_Y;
}
