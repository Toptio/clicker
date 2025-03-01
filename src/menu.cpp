#include "headers/menu.hpp"
#include "headers/game_state.hpp"

extern GameState gameState;

Menu::Menu() {
}

Menu::~Menu() {
    
}

void Menu::Draw() {
    DrawFPS(10, 10);
    DrawText("Press Enter to Start", textX, textY, 20, WHITE);
}

void Menu::Update() {
    if (IsKeyPressed(KEY_ENTER)) {
        gameState = GameState::GAME;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        gameState = GameState::QUIT;
    }

}