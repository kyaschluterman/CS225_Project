#ifndef FRUIT
#define FRUIT
#include "raylib.h"
#include <string>
#include <cstdlib>
#include "globals.h"
#include "Snake.h"

// Abstract base class for fruit objects
class Fruit {
protected:
	int col, row; // Map coordinates 
public:
	// Constructor
	Fruit(int col, int row);
	// Returns row position on map
	int GetRow() { return row; }
	// Returns column position on map
	int GetCol() { return col; }
	// Returns whether snake head is same position as fruit 
	bool Collide(Snake& snake);
	// Draws fruit texture on screen
	virtual void Draw() {}
	// Modifies snake depending on type of fruit (dictated by child class)
	virtual void GetEatenBy(Snake& snake) {}
};

// Class for apple
class Apple: public Fruit {
private:
	int speed_to_increase  = 1; // amount to increase snake speed when eaten
public:
	static Texture2D texture; // texture for apple
	// Constructor
	Apple(int col, int row);
	// Increases length and speed of snake by 1
	void GetEatenBy(Snake& snake) override;
	// Draws apple texture to screen
	void Draw() override;
};

// Class for pear
class Pear : public Fruit {
private:
	int speed_to_decrease = 1; // amount to decrease snake speed when eaten
public:
	static Texture2D texture; // texture for pear
	// Constructor
	Pear(int col, int row);
	// Decreases length and speed of snake by 1
	void GetEatenBy(Snake& snake) override;
	// Draws pear texture to screen
	void Draw() override;
};

// Class for gold apple
class GoldApple : public Fruit {
private:
	int length_to_add = 3; // amount to increase snake length when eaten
	int speed_to_increase = 3; // amount to increase snake speed when eaten
public:
	static Texture2D texture; // texture for gold apple
	// Constructor
	GoldApple(int col, int row);
	// Increases length and speed of snake by 3
	void GetEatenBy(Snake& snake) override;
	// Draws gold apple texture to screen
	void Draw() override;
};
#endif