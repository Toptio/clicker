#include "headers/menu.hpp"
#include "headers/game_state.hpp"

extern GameState gameState;

Menu::Menu() {
    // Initialize the menu buttons
    buttonText = "Start";
    int buttonWidth = 200;
    int buttonHeight = 50; 
    startButton = {
        (float)(GetScreenWidth() / 2 - buttonWidth / 2), 
        (float)(GetScreenHeight() / 2 - buttonHeight / 2 - 30), 
        (float)buttonWidth, 
        (float)buttonHeight
    };
    buttonColor = DARKBLUE;
    buttonHoverColor = BLUE;
    isButtonHovered = false;

    optionsButtonText = "Options";
    int optionsButtonWidth = 200;
    int optionsButtonHeight = 50;
    optionsButton = {
        (float)(GetScreenWidth() / 2 - optionsButtonWidth / 2), 
        (float)(GetScreenHeight() / 2 - optionsButtonHeight / 2 + 30), 
        (float)optionsButtonWidth, 
        (float)optionsButtonHeight
    };
    optionsButtonColor = DARKBLUE;
    optionsButtonHoverColor = BLUE;
    isOptionsButtonHovered = false;
}

Menu::~Menu() {
    
}

void Menu::Draw() {
    DrawFPS(10, 10);

    // Draw the start button
    DrawRectangleRec(startButton, isButtonHovered ? buttonHoverColor : buttonColor);
    int btnTextWidth = MeasureText(buttonText, 20);
    DrawText(
        buttonText, 
        (int)(startButton.x + startButton.width / 2 - btnTextWidth / 2), 
        (int)(startButton.y + startButton.height / 2 - 10), 
        20, 
        WHITE
    );

    // Draw the options button
    DrawRectangleRec(optionsButton, isOptionsButtonHovered ? optionsButtonHoverColor : optionsButtonColor);
    int optionsBtnTextWidth = MeasureText(optionsButtonText, 20);
    DrawText(
        optionsButtonText, 
        (int)(optionsButton.x + optionsButton.width / 2 - optionsBtnTextWidth / 2), 
        (int)(optionsButton.y + optionsButton.height / 2 - 10), 
        20, 
        WHITE
    );
}

void Menu::Update() {
    // Update button positions if the window is resized
    startButton.x = GetScreenWidth() / 2 - startButton.width / 2;
    startButton.y = GetScreenHeight() / 2 - startButton.height / 2 - 30;

    optionsButton.x = GetScreenWidth() / 2 - optionsButton.width / 2;
    optionsButton.y = GetScreenHeight() / 2 - optionsButton.height / 2 + 30;

    // Check if mouse is hovering buttons
    Vector2 mousePos = GetMousePosition();
    isButtonHovered = CheckCollisionPointRec(mousePos, startButton);
    isOptionsButtonHovered = CheckCollisionPointRec(mousePos, optionsButton);

    // Check for button clicks
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (isButtonHovered) {
            gameState = GameState::GAME;
        } else if (isOptionsButtonHovered) {
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        gameState = GameState::GAME;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        gameState = GameState::QUIT;
    }
}