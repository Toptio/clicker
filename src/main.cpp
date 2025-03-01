#include <raylib.h>
#include <stdlib.h>
#include "headers/game_state.hpp"
#include "headers/cookie.hpp"
#include "headers/cursor.hpp"

#define STORAGE_DATA_FILE "save.data"

typedef enum {
    STORAGE_POSITION_SCORE = 0,
} StorageData;

static bool SaveStorageValue(unsigned int position, int value);
static int LoadStorageValue(unsigned int position);

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

void UpdateGame(Cookie& cookie) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    DrawText(TextFormat("Cookies: %d", cookie.GetCookieCount()), 10, 30, 20, WHITE);
    cookie.Draw();
    cookie.Update();
    DrawRectangle(screenWidth - 100, 0, 100, screenHeight, Fade(WHITE, 0.5f));
    if(IsKeyPressed(KEY_ESCAPE)) {
        gameState = GameState::MENU;
    }
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Cookie Clicker");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    InitAudioDevice();

    Music music = LoadMusicStream("assets/sound/game_music.mp3");
    music.looping = true;

    PlayMusicStream(music);

    bool fullScreen = false;

    Cookie cookie;
    Cursor cursor;

    HideCursor();

    Vector2 mousePoint;

    while (!WindowShouldClose()) {

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

        if(IsKeyPressed(KEY_S)) {
            SaveStorageValue(STORAGE_POSITION_SCORE, cookie.GetCookieCount());
        }

        if(IsKeyPressed(KEY_R)) {
            int loadedscore = LoadStorageValue(STORAGE_POSITION_SCORE);
            cookie.SetCookieCount(loadedscore);
            TraceLog(LOG_INFO, "Loaded score: %d", loadedscore);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        mousePoint = GetMousePosition();

        switch(gameState) {
            case GameState::MENU:
                UpdateMenu();
                break;
            case GameState::GAME:
                UpdateGame(cookie);
                break;
            case GameState::QUIT:
                UpdateQuit();
                break;
        }

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

bool SaveStorageValue(unsigned int position, int value) {
    bool success = false;
    int dataSize = 0;
    unsigned int newDataSize = 0;
    unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);
    unsigned char *newFileData = NULL;

    if(fileData != NULL){
        if(dataSize <= static_cast<int>(position*sizeof(int))) {
            newDataSize = (position + 1) * sizeof(int);
            newFileData = (unsigned char *)RL_REALLOC(fileData, newDataSize);

            if(newFileData != NULL) {
                int *dataPtr = (int *)newFileData;
                dataPtr[position] = value;
            } 
            else {
                TraceLog(LOG_WARNING, "Failed to reallocate memory for file data", STORAGE_DATA_FILE, dataSize, position*sizeof(int));
                newFileData = fileData;
                newDataSize = dataSize;
            }
            
        } 
        else {
            newFileData = fileData;
            newDataSize = dataSize;

            int *dataPtr = (int *)newFileData;
            dataPtr[position] = value;
        }
            success = SaveFileData(STORAGE_DATA_FILE, newFileData, newDataSize);
            RL_FREE(newFileData);

            TraceLog(LOG_INFO, "Saved data to file", STORAGE_DATA_FILE, position, value);
        }
        else {
            TraceLog(LOG_WARNING, "Failed to load file data", STORAGE_DATA_FILE);

            dataSize = (position + 1) * sizeof(int);
            fileData = (unsigned char *)RL_MALLOC(dataSize);
            int *dataPtr = (int *)fileData;
            dataPtr[position] = value;

            success = SaveFileData(STORAGE_DATA_FILE, fileData, dataSize);
            UnloadFileData(fileData);

            TraceLog(LOG_INFO, "Saved data to file", STORAGE_DATA_FILE, position, value);
        }

        return success;
}

int LoadStorageValue(unsigned int position)
{
    int value = 0;
    int dataSize = 0;
    unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);

    if (fileData != NULL)
    {
        if (dataSize < ((int)(position*4))) TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", STORAGE_DATA_FILE, position);
        else
        {
            int *dataPtr = (int *)fileData;
            value = dataPtr[position];
        }

        UnloadFileData(fileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", STORAGE_DATA_FILE, value);
    }

    return value;
}