#pragma once
#include <string>
#include <cstdlib>
#include "raylib.h"
#include "config.h"
#include <iostream>
using namespace std;

class Segment {
private:
	int row, col;
	Texture2D texture;
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
		texture = LoadTexture("snake.png");
	}
	int GetRow() { return row; }
	int GetCol() { return col; }
	int GetDir() {
		if (IsHead()) {
			return UP; // for debugging, need to find way for head to know dir
		}
		else {
			if (seg_ahead->GetCol() == col + 1 && seg_ahead->GetRow() == row) {
				return RIGHT;
			}
			else if (seg_ahead->GetCol() == col - 1 && seg_ahead->GetRow() == row) {
				return LEFT;
			}
			else if (seg_ahead->GetCol() == col && seg_ahead->GetRow() == row + 1) {
				return DOWN;
			}
			else if (seg_ahead->GetCol() == col && seg_ahead->GetRow() == row - 1) {
				return UP;
			}
			else {
				return UP; // for debugging
			}
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
	void Update() {
		int cell_x = GetCellX(col);
		int cell_y = GetCellY(row);
		DrawTexture(texture, cell_x, cell_y, WHITE);
	}
};

class Snake {
private:
	int row, col;
	int spawn_row, spawn_col;
	int dir;
	int length = 1;
	Segment* head;
	double speed = 10;
	double init_time = 0;
	double delta_time = 0;
public:
	Snake(int col, int row, int dir = UP) {
		this->col = col;
		this->row = row;
		this->spawn_col = col;
		this->spawn_row = row;
		this->dir = dir;
		this->init_time = GetTime();
		head = new Segment(col, row);
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
			seg->SetPos(seg_ahead->GetCol(),seg_ahead->GetRow());
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
	void IncreaseLength() {
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
		Segment* new_tail = new Segment(new_tail_col,new_tail_row,old_tail);
		length++;
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
	void Reset() {
		DecreaseLength(length - 2);  // This will decrease length to 1
		col = spawn_col;
		row = spawn_row;
		dir = UP;
		speed = 10;
		head->SetPos(col, row);  // Ensure head position is reset
		cout << length<<endl;
	}

	void Update() {
		Segment* seg = head;
		while (seg != nullptr) {
			seg->Update();
			seg = seg->seg_behind;
		}

		delta_time = GetTime() - init_time;
		if (delta_time > (1 / speed)) {
			init_time = GetTime();
			Move();
		}
	}
};