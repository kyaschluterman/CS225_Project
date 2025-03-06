#include "raylib.h"
#include "resource_dir.h"
#include <deque>
#include <cstdlib>
#include <time.h>
#include <vector>
#include "config.h"
#include "Fruit.h"
#include "Snake.h"
using namespace std;

void SpawnFruit(vector<Fruit*>& fruits, int amount, string type) {
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
            if (type == "apple") {
                fruits.push_back(new Apple(col, row));  // Store dynamically allocated Apple
            }
            else if (type == "pear") {
                fruits.push_back(new Pear(col, row));  // Store dynamically allocated Pear
            }
        }
    }
}

int main() {
    // Setup
    srand(time(0));
    InitWindow(WIDTH, HEIGHT, NAME);
    SetTargetFPS(FPS);
    SearchAndSetResourceDir("resources");
    bool game_over = false;

    // Textures
    Texture2D bg_texture = LoadTexture("grass.png");
    Apple::texture = LoadTexture("apple.png");
    Pear::texture = LoadTexture("pear.png");

    // Objects
    vector<Fruit*> fruits;

    Snake* snake = new Snake(1, 6);
    snake->IncreaseLength();
    snake->IncreaseLength();
    snake->IncreaseLength();
    snake->IncreaseLength();
    snake->IncreaseLength();
    snake->IncreaseLength();

    // Spawn Fruits
    SpawnFruit(fruits, 5, "apple");
    SpawnFruit(fruits, 5, "pear");

    InitAudioDevice();
    Music music = LoadMusicStream("music.mp3");
    PlayMusicStream(music);

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

        if (!game_over) { // if snakes are alive
            DrawText("SNAKE!", 10, 10, 25, BLACK);

            snake->Update();

            for (Fruit* fruit : fruits) {  // Use pointer access
                if (fruit->Collide(*snake)) {
                    fruit->GetEatenBy(*snake);
                    fruits.erase(std::remove(fruits.begin(), fruits.end(), fruit), fruits.end());
                }
            }

            if (IsKeyDown(KEY_W)) {
                snake->Turn(UP);
            }
            else if (IsKeyDown(KEY_A)) {
                snake->Turn(LEFT);
            }
            else if (IsKeyDown(KEY_S)) {
                snake->Turn(DOWN);
            }
            else if (IsKeyDown(KEY_D)) {
                snake->Turn(RIGHT);
            }

            if (snake->CollideSelf()) {
                game_over = true;
            }
        }
        else { // if snake dies
            DrawText("GAME OVER! Press 'R' to Restart.", 10, 10, 25, BLACK);
            if (IsKeyDown(KEY_R)) {
                game_over = false;
                snake->Reset();
                SpawnFruit(fruits, 5, "apple");
                SpawnFruit(fruits, 5, "pear");
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