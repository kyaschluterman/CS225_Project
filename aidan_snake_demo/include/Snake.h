#ifndef SNAKE
#define SNAKE
#include <string>
#include <cstdlib>
#include "raylib.h"
#include "globals.h"
#include <iostream>
#include "Obstacle.h"
using namespace std;

// Class for segment of snake
class Segment {
private:
	int row, col; // Current map coordinates
	Rectangle source_rect = { 0, 0, 16, 16 }; // Source rect for drawing textures using DrawTexturePro
	Rectangle dest_rect = { 0, 0, 16, 16 }; // Destination rect for drawing textures using DrawTexturePro
public:
	Segment* seg_ahead; // Pointer to segment ahead of this segment (nullptr if none)
	Segment* seg_behind = nullptr; // Pointer to segment behind this segment (nullptr if none)
	// Constructor
	Segment(int col, int row, Segment* seg_ahead = nullptr);
	// Returns row position on map
	int GetRow() { return row; }
	// Returns column position on map
	int GetCol() { return col; }
	// Returns direction segment is moving
	int GetDir();
	// Links an existing segment behind this
	void AddSegmentBehind(Segment* seg_behind) { this->seg_behind = seg_behind; }
	// Returns whether segment is head of snake
	bool IsHead();
	// Returns whether segment is tail of snake
	bool IsTail();
	// Sets map coordinates of segment
	void SetPos(int col, int row);
	// Updates segment appearance on screen
	void Update(Texture2D texture, int dir);
};

// Class for snake
class Snake {
private:
	int row, col; // Current map coordinates of snake head
	int spawn_row, spawn_col; // Initial coordinates of snake head
	int dir; // Current direction snake is moving
	int length = 2; // Number of segments in snake
	Segment* head; // Pointer to foremost segment
	double speed = 5; // Current speed of snake in map cells per second
	double spawn_speed = speed; // Initial speed of snake in map units per second
	double init_time = 0; // Timestamp to 
	double delta_time = 0; // Time since last recorded timestamp
	int player; // Player number (1 or 2)
	Texture2D head_texture, body_texture, tail_texture, turn_texture; // Textures for snake segments
public:
	// Constructor
	Snake(int col, int row, int player = 1, int dir = RIGHT);
	// Destructor
	~Snake();
	// Returns column position on map
	int GetCol() { return col; }
	// Returns row position on map
	int GetRow() { return row; }
	// Returns number of segments in snake
	int GetLength() { return length; }
	// Changes the direction of the snake's movement
	void Turn(int dir);
	// Moves the snake forward one unit in the direction of movement
	void Move();
	// Returns a pointer to the snakes foremost segment
	Segment* GetHead() { return head; }
	Segment* GetTail();
	// Returns pointer to (num)th segment of snake
	Segment* GetSeg(int num);
	// Adds (amount) segments to rear of snake
	void operator+=(const int amount);
	// Adds one segment to rear of snake
	Snake& operator++(int);
	// Deletes (amount) segments from rear of snake
	void operator-=(const int amount);
	// Deletes (amount) segments from rear of snake
	Snake& operator--(int);
	// Increases speed by (delta_speed), decreases if (delta_speed) is negative
	void AddSpeed(int delta_speed);
	// Returns whether snake head is at same position as another of its segments
	bool CollideSelf();
	// Returns whether snake head is outside of map bounds and/or at same position as obstacle object (o)
	bool CollideWall(Obstacle& o);
	// Returns whether snake head is at same position as a segment of another snake
	bool CollideSnake(Snake& s);
	// Resets snake position, length, and speed
	void Reset();
	// Updates snake appearance on screen
	void Update();
};
#endif