#pragma once
#include "raylib.h"
#include <string>
#include <cstdlib>
#include "config.h"

class Fruit {
protected:
	Texture2D texture;
	int col, row;
public:
	Fruit(int col, int row) {
		if (col > 0 && row > 0 && col <= COLS && row <= ROWS) {
			this->col = col;
			this->row = row;
		}
		else {
			this->col = 1;
			this->row = 1;
		}
		texture = LoadTexture("apple.png");
	}
	int GetRow() { return row; }
	int GetCol() { return col; }
	void Draw() {
		int cell_x = col * CELL_SIZE + CELL_ORIGIN_X;
		int cell_y = row * CELL_SIZE + CELL_ORIGIN_Y;
		DrawTexture(texture, cell_x, cell_y, WHITE);
	}
	virtual void Eat() {}
};

class Apple: public Fruit {
private:
	int length_to_add = 1;
public:
	Apple(int col, int row) : Fruit(col, row) {
		texture = LoadTexture("apple.png");
	}
	void Eat() override {

	}
};