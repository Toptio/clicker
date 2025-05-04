#include "headers/menu.hpp"
#include "headers/game_state.hpp"

extern GameState gameState;

Menu::Menu() {
}

Menu::~Menu() {
    
}

void Menu::Draw() {
    DrawFPS(10, 10);
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    const char* startText = "Press Enter to Start";
    const char* saveText = "CONTROL + S to save game";
    const char* loadText = "CONTROL + R to load game";
    const char* quitText = "Press ESC to Quit";

    int startTextWidth = MeasureText(startText, 20);
    int saveTextWidth = MeasureText(saveText, 20);
    int loadTextWidth = MeasureText(loadText, 20);
    int quitTextWidth = MeasureText(quitText, 20);

    int textX = (screenWidth - startTextWidth) / 2;
    int textY = screenHeight / 2 - 60;

    DrawText(startText, textX, textY, 20, WHITE);
    DrawText(saveText, (screenWidth - saveTextWidth) / 2, textY + 30, 20, WHITE);
    DrawText(loadText, (screenWidth - loadTextWidth) / 2, textY + 60, 20, WHITE);
    DrawText(quitText, (screenWidth - quitTextWidth) / 2, textY + 90, 20, WHITE);
}

void Menu::Update() {
    if (IsKeyPressed(KEY_ENTER)) {
        gameState = GameState::GAME;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        gameState = GameState::QUIT;
    }
}