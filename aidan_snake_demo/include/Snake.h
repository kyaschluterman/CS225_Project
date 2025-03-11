#pragma once
#include <string>
#include <cstdlib>
#include "raylib.h"
#include "config.h"
#include <iostream>
#include "Obstacle.h"
using namespace std;

class Segment {
private:
	int row, col;
	Rectangle sourceRect = { 0, 0, 16, 16 };
	Rectangle destRect = { 0, 0, 16, 16 };
public:
	Segment* seg_ahead;
	Segment* seg_behind = nullptr;
	Segment(int col, int row, Segment* seg_ahead = nullptr) {
		this->col = col;
		this->row = row;
		this->seg_ahead = seg_ahead;
		if (seg_ahead != nullptr) {
			this->seg_ahead->AddSegmentBehind(this);
		}
	}
	int GetRow() { return row; }
	int GetCol() { return col; }
	int GetDir() {
		if (IsHead() && seg_behind) {
			if (seg_behind->GetCol() == col + 1) {
				return LEFT;
			}
			else if (seg_behind->GetCol() == col - 1) {
				return RIGHT;
			}
			else if (seg_behind->GetRow() == row + 1) {
				return UP;
			}
			else if (seg_behind->GetRow() == row - 1) {
				return DOWN;
			}
			else {
				return UP; // for debugging
			}
		}
		else if (!IsHead() && seg_ahead) {
			if (seg_ahead->GetCol() == col + 1) {
				return RIGHT;
			}
			else if (seg_ahead->GetCol() == col - 1) {
				return LEFT;
			}
			else if (seg_ahead->GetRow() == row + 1) {
				return DOWN;
			}
			else if (seg_ahead->GetRow() == row - 1) {
				return UP;
			}
			else {
				return UP; // for debugging
			}
		}
		else {
			return UP;
		}
	}
	void AddSegmentBehind(Segment* seg_behind) {
		this->seg_behind = seg_behind;
	}
	bool IsHead() {
		if (seg_ahead == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	bool IsTail() {
		if (seg_behind == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	void SetPos(int col, int row) {
		this->col = col;
		this->row = row;
	}
	void Update(Texture2D texture, int dir) {
		int cell_x = GetCellX(col);
		int cell_y = GetCellY(row);
		destRect.x = cell_x + texture.width / 2;
		destRect.y = cell_y + texture.height / 2;
		Vector2 origin = { destRect.width / 2, destRect.height / 2 };
		float rotation = (dir == RIGHT) ? 90 : (dir == DOWN) ? 180 : (dir == LEFT) ? 270 : 0;
		DrawTexturePro(texture, sourceRect, destRect, origin, rotation, WHITE);
	}
};

class Snake {
private:
	int row, col;
	int spawn_row, spawn_col;
	int dir;
	int length = 2;
	Segment* head;
	double speed = 5;
	double spawn_speed = speed;
	double init_time = 0;
	double delta_time = 0;
	int player;
	Texture2D head_texture, body_texture, tail_texture, turn_texture;
public:
	Snake(int col, int row, int player = 1, int dir = RIGHT) {
		this->col = col;
		this->row = row;
		this->spawn_col = col;
		this->spawn_row = row;
		this->dir = dir;
		this->init_time = GetTime();
		this->player = player;
		head = new Segment(col, row);
		Segment* tail = new Segment(col, row + 1, head);
		if (player == 1) {
			head_texture = LoadTexture("head.png");
			body_texture = LoadTexture("body.png");
			tail_texture = LoadTexture("tail.png");
			turn_texture = LoadTexture("turn.png");
		}
		else if (player == 2) {
			head_texture = LoadTexture("head2.png");
			body_texture = LoadTexture("body2.png");
			tail_texture = LoadTexture("tail2.png");
			turn_texture = LoadTexture("turn2.png");
		}
	}
	~Snake() {
		Segment* current = head;
		while (current != nullptr) {
			Segment* next = current->seg_behind;
			delete current;
			current = next;
		}
	}
	int GetCol() { return col; }
	int GetRow() { return row; }
	int GetLength() { return length; }
	void Turn(int dir) {
		if ((dir == UP && this->dir == DOWN) || (dir == DOWN && this->dir == UP) || (dir == LEFT && this->dir == RIGHT) || (dir == RIGHT && this->dir == LEFT)) {
			// do nothing
		}
		else {
			this->dir = dir;
		}
	}
	void Move() {
		if (dir == UP) {
			row--;
		}
		else if (dir == DOWN) {
			row++;
		}
		else if (dir == LEFT) {
			col--;
		}
		else if (dir == RIGHT) {
			col++;
		}

		Segment* seg = GetTail();
		Segment* seg_ahead = seg->seg_ahead;
		do {
			seg->SetPos(seg_ahead->GetCol(), seg_ahead->GetRow());
			seg = seg_ahead;
			seg_ahead = seg_ahead->seg_ahead;
		} while (!seg->IsHead());
		head->SetPos(col, row);
	}
	Segment* GetHead() { return head; }
	Segment* GetTail() {
		Segment* seg = head;
		while (!seg->IsTail()) {
			seg = seg->seg_behind;
		}
		return seg;
	}
	Segment* GetSeg(int num) {
		int seg_num = 0;
		Segment* seg = head;
		while (seg_num < num) {
			seg = seg->seg_behind;
			seg_num++;
		}
		return seg;
	}
	void IncreaseLength(int amount) {
		for (int i = 0; i < amount; i++) {
			Segment* old_tail = GetTail();
			int new_tail_col = old_tail->GetCol();
			int new_tail_row = old_tail->GetRow();
			std::cout << old_tail->GetDir() << std::endl;
			if (old_tail->GetDir() == UP) {
				new_tail_row++;
			}
			else if (old_tail->GetDir() == DOWN) {
				new_tail_row--;
			}
			else if (old_tail->GetDir() == LEFT) {
				new_tail_col++;
			}
			else if (old_tail->GetDir() == RIGHT) {
				new_tail_col--;
			}
			Segment* new_tail = new Segment(new_tail_col, new_tail_row, old_tail);
			length++;
		}
	}
	void DecreaseLength(int amount) {
		if (amount < length - 1) {
			Segment* tail = GetTail();
			for (int i = 0; i < amount; i++) {
				Segment* new_tail = tail->seg_ahead;
				delete tail;
				tail = new_tail;
				length--;
			}
			tail->seg_behind = nullptr;
		}
	}
	void AddSpeed(int delta_speed) {
		if (speed + delta_speed > 0) {
			speed += delta_speed;
		}
	}
	bool CollideSelf() {
		bool collision = false;
		Segment* seg = head->seg_behind;
		while (seg != nullptr) {
			if (col == seg->GetCol() && row == seg->GetRow()) {
				return true;
			}
			seg = seg->seg_behind;
		}
		return collision;
	}
	bool CollideWall(Obstacle & o) {
		if (o.Collision(col, row)) {
			return true;
		}
		if (row >= ROWS + 1 || row <= 0 || col >= COLS + 1 || col <= 0) {
			return true;
		}
		return false;
	}
	bool CollideSnake(Snake & s) {
		bool collision = false;
		Segment* seg = s.head;
		while (seg != nullptr) {
			if (col == seg->GetCol() && row == seg->GetRow()) {
				return true;
			}
			seg = seg->seg_behind;
		}
		return collision;
	}
	void Reset() {
		DecreaseLength(length - 2);  // This will decrease length to 1
		col = spawn_col;
		row = spawn_row;
		dir = RIGHT;
		speed = spawn_speed;
		head->SetPos(col, row);  // Ensure head position is reset
		cout << length << endl;
	}
	void Update() {
		if (player == 1) {
			if (IsKeyDown(KEY_W)) {
				Turn(UP);
			}
			else if (IsKeyDown(KEY_A)) {
				Turn(LEFT);
			}
			else if (IsKeyDown(KEY_S)) {
				Turn(DOWN);
			}
			else if (IsKeyDown(KEY_D)) {
				Turn(RIGHT);
			}
		}
		else if (player == 2) {
			if (IsKeyDown(KEY_UP)) {
				Turn(UP);
			}
			else if (IsKeyDown(KEY_LEFT)) {
				Turn(LEFT);
			}
			else if (IsKeyDown(KEY_DOWN)) {
				Turn(DOWN);
			}
			else if (IsKeyDown(KEY_RIGHT)) {
				Turn(RIGHT);
			}
		}

		Segment* seg = head;
		while (seg != nullptr) {
			if (seg->IsHead()) {
				seg->Update(head_texture, seg->GetDir());
			}
			else if (seg->IsTail()) {
				seg->Update(tail_texture, seg->GetDir());
			}
			else {
				int ahead_col = seg->seg_ahead->GetCol();
				int ahead_row = seg->seg_ahead->GetRow();
				int behind_col = seg->seg_behind->GetCol();
				int behind_row = seg->seg_behind->GetRow();
				if (ahead_col == seg->GetCol() && behind_col == seg->GetCol()) { // if segs in same column
					seg->Update(body_texture, UP);
				}
				else if (ahead_row == seg->GetRow() && behind_row == seg->GetRow()) { // if segs in same row
					seg->Update(body_texture, RIGHT);
				}
				else if ((ahead_col == seg->GetCol() + 1 && behind_col == seg->GetCol() && behind_row == seg->GetRow() + 1) || (behind_col == seg->GetCol() + 1 && ahead_col == seg->GetCol() && ahead_row == seg->GetRow() + 1)) { // if turning from up to right
					seg->Update(turn_texture, UP);
				}
				else if ((ahead_col == seg->GetCol() + 1 && behind_col == seg->GetCol() && behind_row == seg->GetRow() - 1) || (behind_col == seg->GetCol() + 1 && ahead_col == seg->GetCol() && ahead_row == seg->GetRow() - 1)) { // if turning from down to right
					seg->Update(turn_texture, LEFT);
				}
				else if ((ahead_col == seg->GetCol() - 1 && behind_col == seg->GetCol() && behind_row == seg->GetRow() + 1) || (behind_col == seg->GetCol() - 1 && ahead_col == seg->GetCol() && ahead_row == seg->GetRow() + 1)) { // if turning from up to left
					seg->Update(turn_texture, RIGHT);
				}
				else if ((ahead_col == seg->GetCol() - 1 && behind_col == seg->GetCol() && behind_row == seg->GetRow() - 1) || (behind_col == seg->GetCol() - 1 && ahead_col == seg->GetCol() && ahead_row == seg->GetRow() - 1)) { // if turning from down to left
					seg->Update(turn_texture, DOWN);
				}
			}
			seg = seg->seg_behind;
		}

		delta_time = GetTime() - init_time;
		if (delta_time > (1 / speed)) {
			init_time = GetTime();
			Move();
		}
	}
};