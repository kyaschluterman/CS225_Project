#include "raylib.h"
#include "resource_dir.h"
#include <deque>
#include <cstdlib>
#include <time.h>
#include "config.h"
#include "Fruit.h"
#include "Snake.h"

int main() {
    
    // Setup
    srand(time(0));
    InitWindow(WIDTH, HEIGHT, NAME);
    SetTargetFPS(FPS);
    SearchAndSetResourceDir("resources");

    // Textures
    Texture2D bg_texture = LoadTexture("grass.png");

    // Objects
    Apple* apples[MAX_FRUIT];
    for (int i = 0; i < MAX_FRUIT; i++) {
        apples[i] = nullptr;
    }
    int apple_count = 0;

    Snake* snake = new Snake(1, 6);
    snake->IncreaseLength();
    snake->IncreaseLength();
    snake->IncreaseLength();
    snake->IncreaseLength();
    snake->IncreaseLength();

    InitAudioDevice();
    Music music = LoadMusicStream("music.mp3");
    PlayMusicStream(music);

    for (int col = 1; col <= COLS; col++) {
        for (int row = 1; row <= ROWS; row++) {
            int place = rand() % 100;
            if (place == 0) {
                apples[apple_count] = new Apple(col, row);
                apple_count++;
            }
        }
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        UpdateMusicStream(music);

        // Draw Background
        for (int col = 0; col <= COLS + 1; col++) {
            for (int row = 0; row <= ROWS + 1; row++) {
                int cell_x = col * CELL_SIZE + CELL_ORIGIN_X;
                int cell_y = row * CELL_SIZE + CELL_ORIGIN_Y;
                if (col == 0 || row == 0 || col == COLS + 1 || row == ROWS + 1) {
                    DrawRectangle(cell_x, cell_y, CELL_SIZE, CELL_SIZE, BLACK);
                }
                else {
                    DrawTexture(bg_texture, cell_x, cell_y, WHITE);
                }
            }
        }

        // Draw Objects
        for (int i = 0; i < MAX_FRUIT; i++) {
            if (apples[i]) {
                apples[i]->Draw();
            }
        }

        // Events

        if (snake) {
            snake->Draw();

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

            if (snake->GetCol() > COLS || snake->GetRow() > ROWS || snake->GetCol() < 1 || snake->GetRow() < 1) {
                delete snake;
                snake = nullptr;
            }
        }

        EndDrawing();
    }

    UnloadTexture(bg_texture);

    CloseWindow();

    return 0;
}