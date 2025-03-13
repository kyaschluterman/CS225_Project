#include "Snake.h"
using namespace std;

// Constructor
Segment::Segment(int col, int row, Segment* seg_ahead) {
	this->col = col;
	this->row = row;
	this->seg_ahead = seg_ahead;
	if (seg_ahead != nullptr) {
		this->seg_ahead->AddSegmentBehind(this);
	}
}
int Segment::GetDir() {
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
// Returns whether segment is head of snake
bool Segment::IsHead() {
	if (seg_ahead == nullptr) {
		return true;
	}
	else {
		return false;
	}
}
// Returns whether segment is tail of snake
bool Segment::IsTail() {
	if (seg_behind == nullptr) {
		return true;
	}
	else {
		return false;
	}
}
// Sets map coordinates of segment
void Segment::SetPos(int col, int row) {
	this->col = col;
	this->row = row;
}
// Updates segment appearance on screen
void Segment::Update(Texture2D texture, int dir) {
	int cell_x = GetCellX(col);
	int cell_y = GetCellY(row);
	dest_rect.x = cell_x + texture.width / 2;
	dest_rect.y = cell_y + texture.height / 2;
	Vector2 origin = { dest_rect.width / 2, dest_rect.height / 2 };
	float rotation = (dir == RIGHT) ? 90 : (dir == DOWN) ? 180 : (dir == LEFT) ? 270 : 0;
	DrawTexturePro(texture, source_rect, dest_rect, origin, rotation, WHITE);
}

// Constructor
Snake::Snake(int col, int row, int player, int dir) {
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
// Destructor
Snake::~Snake() {
	Segment* current = head;
	while (current != nullptr) {
		Segment* next = current->seg_behind;
		delete current;
		current = next;
	}
}
// Changes the direction of the snake's movement
void Snake::Turn(int dir) {
	if ((dir == UP && this->dir == DOWN) || (dir == DOWN && this->dir == UP) || (dir == LEFT && this->dir == RIGHT) || (dir == RIGHT && this->dir == LEFT)) {
		// do nothing
	}
	else {
		this->dir = dir;
	}
}
// Moves the snake forward one unit in the direction of movement
void Snake::Move() {
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
Segment* Snake::GetTail() {
	Segment* seg = head;
	while (!seg->IsTail()) {
		seg = seg->seg_behind;
	}
	return seg;
}
// Returns pointer to (num)th segment of snake
Segment* Snake::GetSeg(int num) {
	int seg_num = 0;
	Segment* seg = head;
	while (seg_num < num) {
		seg = seg->seg_behind;
		seg_num++;
	}
	return seg;
}
// Adds (amount) segments to rear of snake
void Snake::operator+=(const int amount) {
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
// Adds one segment to rear of snake
Snake& Snake::operator++(int) {
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
	return *this;
}
// Deletes (amount) segments from rear of snake
void Snake::operator-=(const int amount) {
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
// Deletes (amount) segments from rear of snake
Snake& Snake::operator--(int) {
	if (length > 2) {
		Segment* tail = GetTail();
		Segment* new_tail = tail->seg_ahead;
		delete tail;
		tail = new_tail;
		length--;
		tail->seg_behind = nullptr;
	}
	return *this;
}
// Increases speed by (delta_speed), decreases if (delta_speed) is negative
void Snake::AddSpeed(int delta_speed) {
	if (speed + delta_speed > 0) {
		speed += delta_speed;
	}
}
// Returns whether snake head is at same position as another of its segments
bool Snake::CollideSelf() {
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
// Returns whether snake head is outside of map bounds and/or at same position as obstacle object (o)
bool Snake::CollideWall(Obstacle& o) {
	if (o.Collision(col, row)) {
		return true;
	}
	if (row >= ROWS + 1 || row <= 0 || col >= COLS + 1 || col <= 0) {
		return true;
	}
	return false;
}
// Returns whether snake head is at same position as a segment of another snake
bool Snake::CollideSnake(Snake& s) {
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
// Resets snake position, length, and speed
void Snake::Reset() {
	*this -= (length - 2);  // This will decrease length to 1
	col = spawn_col;
	row = spawn_row;
	dir = RIGHT;
	speed = spawn_speed;
	head->SetPos(col, row);  // Ensure head position is reset
	cout << length << endl;
}
// Updates snake appearance on screen
void Snake::Update() {
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