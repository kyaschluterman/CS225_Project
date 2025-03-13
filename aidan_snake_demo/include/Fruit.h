#ifndef FRUIT
#define FRUIT
#include "raylib.h"
#include <string>
#include <cstdlib>
#include "globals.h"
#include "Snake.h"

class Fruit {
protected:
	int col, row;
public:
	Fruit(int col, int row);
	int GetRow() { return row; }
	int GetCol() { return col; }
	bool Collide(Snake& snake);
	virtual void Draw() {}
	virtual void GetEatenBy(Snake& snake) {}
};

class Apple: public Fruit {
private:
	int speed_to_increase  = 1;
public:
	static Texture2D texture;
	Apple(int col, int row);
	void GetEatenBy(Snake& snake) override;
	void Draw() override;
};

class Pear : public Fruit {
private:
	int speed_to_decrease = 1;
public:
	static Texture2D texture;
	Pear(int col, int row);
	void GetEatenBy(Snake& snake) override;
	void Draw() override;
};

class GoldApple : public Fruit {
private:
	int length_to_add = 3;
	int speed_to_increase = 3;
public:
	static Texture2D texture;
	GoldApple(int col, int row);
	void GetEatenBy(Snake& snake);
	void Draw() override;
};
#endif