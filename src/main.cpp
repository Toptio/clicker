#include <raylib.h>
#include <stdlib.h>
#include "headers/game_state.hpp"
#include "headers/save.hpp"
#include "headers/cookie.hpp"
#include "headers/upgrades.hpp"
#include "headers/cursor.hpp"

// Initial game state
GameState gameState = GameState::MENU;

void UpdateQuit() {
    const char* text = "Are you sure you want to exit? Y/N";
    int textWidth = MeasureText(text, 20);
    int textX = GetScreenWidth() / 2 - textWidth / 2;
    int textY = GetScreenHeight() / 2;
    DrawText(text, textX, textY, 20, WHITE);
    if (IsKeyPressed(KEY_Y)) {
        CloseWindow();
    }
    if (IsKeyPressed(KEY_N)) {
        gameState = GameState::MENU;
    }
}

void UpdateMenu() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int textWidth = MeasureText("Press Enter to Start", 20);
    int textX = (screenWidth - textWidth) / 2;
    int textY = screenHeight / 2;
    DrawText("Press Enter to Start", textX, textY, 20, WHITE);
    if (IsKeyPressed(KEY_ENTER)) {
        gameState = GameState::GAME;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        gameState = GameState::QUIT;
    }
}

void UpdateGame(Cookie& cookie, Upgrades& upgrades) {
    DrawText(TextFormat("Cookies: %d", cookie.GetCookieCount()), 10, 30, 20, WHITE);
    cookie.Draw(), cookie.Update();
    upgrades.Draw(), upgrades.Update(cookie);
    if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) {
        SaveStorageValue(STORAGE_POSITION_SCORE, cookie.GetCookieCount());
    }
    if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_R)) {
        int loadedscore = LoadStorageValue(STORAGE_POSITION_SCORE);
        cookie.SetCookieCount(loadedscore);
        TraceLog(LOG_INFO, "Loaded score: %d", loadedscore);
    }
    if(IsKeyPressed(KEY_ESCAPE)) {
        gameState = GameState::MENU;
    }
}

void UpdateWin() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int textWidth = MeasureText("You won! Press Enter to restart", 20);
    int textX = (screenWidth - textWidth) / 2;
    int textY = screenHeight / 2;
    DrawText("You won! Press Enter to restart", textX, textY, 20, WHITE);
    if (IsKeyPressed(KEY_ESCAPE)) {
        gameState = GameState::MENU;
    }
    if (IsKeyPressed(KEY_ENTER)) {
        gameState = GameState::GAME;
    }
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Cookie Clicker");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    //SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowIcon(LoadImage("assets/icon/icon.png"));

    InitAudioDevice();

    // Load game music
    Music music = LoadMusicStream("assets/sound/game_music.mp3");
    music.looping = true;
    PlayMusicStream(music);

    bool fullScreen = false;

    // Initialize game objects
    Cookie cookie;
    Cursor cursor;
    Upgrades upgrades;

    // Hide cursor and set mouse position
    HideCursor();
    Vector2 mousePoint;

    while (!WindowShouldClose()) {

        // Toggle fullscreen
        if(IsKeyPressed(KEY_F)) {
            if(fullScreen) {
                fullScreen = false;
                ToggleFullscreen();
            }
            else {
                fullScreen = true;
                ToggleFullscreen();
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

            // Get mouse position
            mousePoint = GetMousePosition();

            // Update game state
            switch(gameState) {
                case GameState::MENU:
                    UpdateMenu();
                    break;
                case GameState::GAME:
                    UpdateGame(cookie, upgrades);
                    break;
                case GameState::WIN:
                    UpdateWin();
                    break;  
                case GameState::QUIT:
                    UpdateQuit();
                    break;
            }

            // Update and draw cursor
            cursor.Update(mousePoint);
            cursor.Draw(mousePoint);

        EndDrawing();

        UpdateMusicStream(music);
    }

    UnloadMusicStream(music);
    CloseAudioDevice();

    CloseWindow();

    return 0;
}