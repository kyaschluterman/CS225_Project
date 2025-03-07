#pragma once
#include "raylib.h"
#include <string>
#include <cstdlib>
#include "config.h"
#include "Snake.h"

class Fruit {
protected:
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
	}
	int GetRow() { return row; }
	int GetCol() { return col; }
	bool Collide(Snake & snake) {
		if (snake.GetCol() == col && snake.GetRow() == row) {
			return true;
		}
		else {
			return false;
		}
	}
	virtual void Draw() {}
	virtual void GetEatenBy(Snake & snake) {}
};

class Apple: public Fruit {
private:
	int length_to_add = 1;
	int speed_to_increase  = 1;
public:
	static Texture2D texture;
	Apple(int col, int row) : Fruit(col, row) {
		
	}
	void GetEatenBy(Snake & snake) override {
		snake.IncreaseLength(length_to_add);
		snake.AddSpeed(speed_to_increase);
	}
	void Draw() override {
		DrawTexture(texture, GetCellX(col), GetCellY(row), WHITE);
	}
};
Texture2D Apple::texture;

class Pear : public Fruit {
private:
	int speed_to_decrease = 1;
	int length_to_decrease = 1;
public:
	static Texture2D texture;
	Pear(int col, int row) : Fruit(col, row) {

	}
	void GetEatenBy(Snake & snake) override {
		snake.AddSpeed(-speed_to_decrease);
		snake.DecreaseLength(length_to_decrease);
	}
	void Draw() override {
		DrawTexture(texture, GetCellX(col), GetCellY(row), WHITE);
	}
};
Texture2D Pear::texture;

class GoldApple : public Fruit {
private:
	int length_to_add = 3;
	int speed_to_increase = 3;
public:
	static Texture2D texture;
	GoldApple(int col, int row) : Fruit(col, row) {

	}
	void GetEatenBy(Snake& snake) override {
		snake.IncreaseLength(length_to_add);
		snake.AddSpeed(speed_to_increase);
	}
	void Draw() override {
		DrawTexture(texture, GetCellX(col), GetCellY(row), WHITE);
	}
};
Texture2D GoldApple::texture;