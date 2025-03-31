#include "raylib.h"
#include "resource_dir.h"
#include <deque>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include "globals.h"
#include "Fruit.h"
#include "Snake.h"
#include "Obstacle.h"
using namespace std;

#include <iostream>
#include <fstream>
#include <string>

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

int GetCellX(int col) {
    return col * CELL_SIZE + CELL_ORIGIN_X;
}

int GetCellY(int row) {
    return row * CELL_SIZE + CELL_ORIGIN_Y;
}

void SpawnFruit(vector<Fruit*>& fruits, int amount, const type_info& type) {
    for (int i = 0; i < amount; i++) {
        int col = rand() % COLS + 1;
        int row = rand() % ROWS + 1;

        // Ensure the new apple does not overlap with an existing apple
        bool collision = false;
        for (Fruit* fruit : fruits) {  // Use pointer access
            if (fruit->GetCol() == col && fruit->GetRow() == row) {
                collision = true;
                break;
            }
        }

        if (!collision) {
            if (type == typeid(Apple)) {
                fruits.push_back(new Apple(col, row));  // Store dynamically allocated Apple
            }
            else if (type == typeid(Pear)) {
                fruits.push_back(new Pear(col, row));  // Store dynamically allocated Pear
            }
            else if (type == typeid(GoldApple)) {
                fruits.push_back(new GoldApple(col, row));
            }
        }
    }
}

void ClearFruits(vector<Fruit*>& fruits) {
    for (Fruit* fruit : fruits) {
        delete fruit; // Free allocated memory
    }
    fruits.clear(); // Clear the vector
}

int main() {
    // Setup
    srand(time(0));
    InitWindow(WIDTH, HEIGHT, NAME);
    SetTargetFPS(FPS);
    SearchAndSetResourceDir("resources");
    bool game_over = false;
    bool snake1_wins = false;
    bool snake2_wins = false;

    // Textures
    Texture2D bg_texture = LoadTexture("grass.png");
    Apple::texture = LoadTexture("apple.png");
    Pear::texture = LoadTexture("pear.png");
    GoldApple::texture = LoadTexture("gold_apple.png");

    // Objects
    vector<Fruit*> fruits;

    Obstacle allwalls[NUM_WALLS];

    Snake* snake = new Snake(1, 6, 1);
    Snake* snake2 = new Snake(10, 10, 2);

    // Spawn Fruits
    SpawnFruit(fruits, 3, typeid(Apple));
    SpawnFruit(fruits, 3, typeid(Pear));
    SpawnFruit(fruits, 1, typeid(GoldApple));

    InitAudioDevice();
    Music music = LoadMusicStream("music.mp3");
    PlayMusicStream(music);

    int writeScore = 0;
    int highestscore;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        UpdateMusicStream(music);

        // Draw Background
        for (int col = 0; col <= COLS + 1; col++) {
            for (int row = 0; row <= ROWS + 1; row++) {
                int cell_x = col * CELL_SIZE + CELL_ORIGIN_X - 1;
                int cell_y = row * CELL_SIZE + CELL_ORIGIN_Y - 1;
                if (col == 0 || row == 0 || col == COLS + 1 || row == ROWS + 1) {
                    DrawRectangle(cell_x, cell_y, CELL_SIZE, CELL_SIZE, BLACK);
                }
                else {
                    DrawTexture(bg_texture, cell_x, cell_y, WHITE);
                }
            }
        }

        // Draw Objects
        for (Fruit* fruit : fruits) {
            fruit->Draw();  // Call the correct virtual method
        }

        for (int i = 0; i < NUM_WALLS; i++) {
            allwalls[i].Draw();
        }

        if (!game_over) { // if snakes are alive
            writeScore = 1;
            DrawText("Snake!", 10, 10, 25, BLACK);

            string str1 = "Snake 1 score: " + to_string(snake->GetLength()-2);
            string str2 = "Snake 2 score: " + to_string(snake2->GetLength()-2);
            DrawText( str1.c_str(), 260, 870, 25, BLACK);
            DrawText( str2.c_str(), 550, 870, 25, BLACK);

            for (Fruit* fruit : fruits) {
                if (fruit->Collide(*snake)) {
                    fruit->GetEatenBy(*snake);
                    fruits.erase(remove(fruits.begin(), fruits.end(), fruit), fruits.end());
                    SpawnFruit(fruits, 1, typeid(*fruit));
                }
            }

            for (Fruit* fruit : fruits) {
                if (fruit->Collide(*snake2)) {
                    fruit->GetEatenBy(*snake2);
                    fruits.erase(remove(fruits.begin(), fruits.end(), fruit), fruits.end());
                    SpawnFruit(fruits, 1, typeid(*fruit));
                }
            }

            snake->Update();
            snake2->Update();
            if (snake->CollideSelf() || snake2->CollideSnake(*snake)) {
                snake1_wins = true;
                game_over = true;
            }
            
            if (snake2->CollideSelf() || snake->CollideSnake(*snake2)) {
                snake2_wins = true;
                game_over = true;
            }

            for (int i = 0; i < NUM_WALLS; i++) {
                if (snake->CollideWall(allwalls[i])) {
                    snake2_wins = true;
                    game_over = true;
                }
            }
            for (int i = 0; i < NUM_WALLS; i++) {
                if (snake2->CollideWall(allwalls[i])) {
                    game_over = true;
                    snake1_wins = true;
                }
            }
        }
        else { // if snake dies

            if(writeScore){
                writeScore = 0;
                std::string filename = "Scores.txt";
                std::ofstream outfile(filename, std::ios::app);
                if (outfile.is_open()) {
                    outfile << snake->GetLength() -2 << endl<< snake2->GetLength()-2 << endl;
                    outfile.close();
                }
            }

            highestscore = snake->GetLength()-2;
            //read scores
            int numby; 
            ifstream fin("Scores.txt");
            while( !fin.eof() ){
                fin>>numby;
                if(numby>highestscore){
                    highestscore = numby;
                }
            }
            fin.close();
            string str1 = "Top score: " + to_string(highestscore);



            DrawRectangle( 380, 410, 300, 130, BLACK );
            DrawRectangle( 390, 420, 280, 110, RAYWHITE );
            DrawText( str1.c_str(), 400, 495, 25, BLACK);

            if (snake1_wins) {
                DrawText("Player 1 Wins!", 400, 435, 25, BLACK);
            }
            else if (snake2_wins) {
                DrawText("Player 2 Wins!", 400, 435, 25, BLACK);
            }
            DrawText("Press 'R' to Restart.", 400, 465, 25, BLACK);
            if (IsKeyDown(KEY_R)) {
                
                game_over = false;
                snake1_wins = false;
                snake2_wins = false;
                snake->Reset();
                snake2->Reset();
                ClearFruits(fruits);
                SpawnFruit(fruits, 3, typeid(Apple));
                SpawnFruit(fruits, 3, typeid(Pear));
                SpawnFruit(fruits, 1, typeid(GoldApple));
                for (int i = 0;i < NUM_WALLS;i++) {
                    allwalls[i].Reset();
                }
            }
        }

        EndDrawing();
    }

    UnloadTexture(bg_texture);
    delete snake;
    for (Fruit* fruit : fruits) {
        delete fruit;
    }
    fruits.clear();
    CloseWindow();

    return 0;
}