#include "Fruit.h"

Fruit::Fruit(int col, int row) {
	if (col > 0 && row > 0 && col <= COLS && row <= ROWS) {
		this->col = col;
		this->row = row;
	}
	else {
		this->col = 1;
		this->row = 1;
	}
}

bool Fruit::Collide(Snake& snake) {
	if (snake.GetCol() == col && snake.GetRow() == row) {
		return true;
	}
	else {
		return false;
	}
}

Apple::Apple(int col, int row) : Fruit(col, row) {

}

void Apple::GetEatenBy(Snake& snake) {
	snake++;
	snake.AddSpeed(speed_to_increase);
}

void Apple::Draw() {
	DrawTexture(texture, GetCellX(col), GetCellY(row), WHITE);
}

Texture2D Apple::texture;

Pear::Pear(int col, int row) : Fruit(col, row) {

}

void Pear::GetEatenBy(Snake& snake) {
	snake.AddSpeed(-speed_to_decrease);
	snake--;
}

void Pear::Draw() {
	DrawTexture(texture, GetCellX(col), GetCellY(row), WHITE);
}

Texture2D Pear::texture;

GoldApple::GoldApple(int col, int row) : Fruit(col, row) {

}

void GoldApple::GetEatenBy(Snake& snake) {
	snake += length_to_add;
	snake.AddSpeed(speed_to_increase);
}

void GoldApple::Draw() {
	DrawTexture(texture, GetCellX(col), GetCellY(row), WHITE);
}

Texture2D GoldApple::texture;