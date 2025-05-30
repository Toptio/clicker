#include <raylib.h>
#include <cstring>
#include <string>
#include "headers/game_state.hpp"
#include "headers/upgrades.hpp"
#include "headers/cookie.hpp"

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 40
#define POPUP_DURATION 2.0f

extern GameState gameState;

Upgrades::Upgrades() {
    int screenWidth = GetScreenWidth();

    // Initialize buttons
    buttons.push_back({{(float)screenWidth - (screenWidth * 0.3f) + 10, 50, BUTTON_WIDTH, BUTTON_HEIGHT}, 0, false, "+1 cookie per second", 50, "second", 1, 50, 0.5f});
    buttons.push_back({{(float)screenWidth - (screenWidth * 0.3f) + 10, 100, BUTTON_WIDTH, BUTTON_HEIGHT}, 0, false, "+10 cookies per second", 300, "second", 10, 300, 0.5f});
    buttons.push_back({{(float)screenWidth - (screenWidth * 0.3f) + 10, 150, BUTTON_WIDTH, BUTTON_HEIGHT}, 0, false, "+100 cookie per second", 850, "second", 100, 850, 0.5f});
    buttons.push_back({{(float)screenWidth - (screenWidth * 0.3f) + 10, 200, BUTTON_WIDTH, BUTTON_HEIGHT}, 0, false, "+500 cookies per second", 1500, "second", 500, 1500, 0.5f});

    // Shop buttons
    buttons.push_back({{(float)screenWidth - (screenWidth * 0.3f) + 10, 300, BUTTON_WIDTH, BUTTON_HEIGHT}, 0, false, "+50 cookies per click", 500, "click", 50, 500, 0.5f});
    buttons.push_back({{(float)screenWidth - (screenWidth * 0.3f) + 10, 350, BUTTON_WIDTH, BUTTON_HEIGHT}, 0, false, "+100 cookies per click", 1000, "click", 100, 1000, 0.5f});
    buttons.push_back({{(float)screenWidth - (screenWidth * 0.3f) + 10, 450, BUTTON_WIDTH, BUTTON_HEIGHT}, 0, false, "+250 cookies per click", 2500, "click", 250, 2500, 0.5f});
    buttons.push_back({{(float)screenWidth - (screenWidth * 0.3f) + 10, 400, BUTTON_WIDTH, BUTTON_HEIGHT}, 0, false, "Win button", 1000000, "win", 0, 1000000, 2.2f});
 
    // Initialize other members
    showPopup = false;
    popupTimer = 0.0f;
    popupText = nullptr;
    winCount = 0;
    currentLevel = 1;
}

void Upgrades::Draw() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Define panel
    upgradesPanel = { (float)screenWidth - (screenWidth * 0.3f), 0, screenWidth * 0.3f, (float)screenHeight };

    // Draw upgrades panel
    DrawRectangleRec(upgradesPanel, Fade(WHITE, 0.5f));
    DrawText("Upgrades", screenWidth - (screenWidth * 0.3f) + 10, 10, 20, WHITE);

    // Draw Shop Text
    DrawText("Shop", screenWidth - (screenWidth * 0.3f) + 10, 250, 20, WHITE);


   // Draw buttons
   for (const auto& button : buttons) {
        Color color;
        switch(button.state) {
            case 0: color = RED; break;
            case 1: color = YELLOW; break;
            case 2: color = WHITE; break;
        }
        DrawRectangleRec(button.rect, color);
        DrawTextInButton(button.text, button.rect);
    }

    // Draw popup if visible
    if (showPopup) {
        DrawPopup(popupText);
    }

}

void Upgrades::Draw2(){
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Define panel
    upgradesPanel = { (float)screenWidth - (screenWidth * 0.3f), 0, screenWidth * 0.3f, (float)screenHeight };

    // Draw upgrades panel
    DrawRectangleRec(upgradesPanel, Fade(WHITE, 0.5f));
    DrawText("Upgrades", screenWidth - (screenWidth * 0.3f) + 10, 10, 20, WHITE);

    // Draw Shop Text
    DrawText("Shop", screenWidth - (screenWidth * 0.3f) + 10, 250, 20, WHITE);
}

void Upgrades::Update(Cookie& cookie) {

   // Update buttons
   for (auto& button : buttons) {
        HandleButton(button, cookie);
    }

    // Update popup timer
    if (showPopup) {
        popupTimer -= GetFrameTime();
        if (popupTimer <= 0.0f) {
            showPopup = false;
        }
    }

}

void Upgrades::HandleButton(Button& button, Cookie& cookie) {
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, button.rect)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            button.state = 2; // Pressed
            if (!button.clicked) {
                button.clicked = true;
                CheckButtonClicked(button, cookie);
            }
        } else {
            button.state = 1; // Hover
        }
    } else {
        button.state = 0; // Normal
    }

    if (button.clicked && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        button.clicked = false;
    }
}

void Upgrades::CheckButtonClicked(Button& button, Cookie& cookie) {
    if (cookie.GetCookieCount() >= button.requiredCookies) {
        cookie.SetCookieCount(cookie.GetCookieCount() - button.requiredCookies);
        if (strcmp(button.upgradeType, "click") == 0) {
            cookie.SetCookiePerClick(cookie.GetCookiePerClick() + button.upgradeAmount);
            TraceLog(LOG_INFO, "Cookie per click is now: %d", cookie.GetCookiePerClick());
        } else if (strcmp(button.upgradeType, "mult") == 0) {
            cookie.SetCookiePerClick(cookie.GetCookiePerClick() * button.upgradeAmount);
            TraceLog(LOG_INFO, "Cookie per click is now: %d", cookie.GetCookiePerClick());
        } else if (strcmp(button.upgradeType, "second") == 0) {
            cookie.SetCookiePerSecond(cookie.GetCookiePerSecond() + button.upgradeAmount);
            TraceLog(LOG_INFO, "Cookie per second is now: %d", cookie.GetCookiePerSecond());
        } else if (strcmp(button.upgradeType, "win") == 0) {
            cookie.Reset();
            void ResetUpgrades();
            winCount++;
            TraceLog(LOG_INFO, "Win count: %d", winCount);
            
            // Check if player should level up
            if (winCount >= 2 * currentLevel) {
                currentLevel++;
                winCount = 0;
                TraceLog(LOG_INFO, "Level up! Current level: %d", currentLevel);
                popupText = TextFormat("Level up! You are now level %d!", currentLevel);
                showPopup = true;
                popupTimer = POPUP_DURATION;
            }
            
            gameState = GameState::WIN;
        }
        // Mark button as purchased
        //button.purchased = true;

        // Increase price for next upgrade
        button.requiredCookies = static_cast<int>(button.requiredCookies * button.priceMultiplier);
    } else {
        TraceLog(LOG_INFO, "Not enough cookies: %d", cookie.GetCookieCount());
        TraceLog(LOG_INFO, "Need %d cookies to buy upgrade", button.requiredCookies);
        popupText = TextFormat("Not enough cookies! Need %d cookies to buy upgrade", button.requiredCookies);
        showPopup = true; // Show popup
        popupTimer = POPUP_DURATION; // Reset popup timer
    }
}

void Upgrades::SetRequiredCookies(int index, int requiredCookies) {
    if (index >= 0 && index < static_cast<int>(buttons.size())) {
        buttons[index].requiredCookies = requiredCookies;
    }
}


int Upgrades::GetRequiredCookies(int index) const {
    if (index >= 0 && static_cast<std::vector<Upgrades::Button>::size_type>(index) < buttons.size()) {
        return buttons[index].requiredCookies;
    }
    return -1; // Return -1 if index is out of range
}

void Upgrades::SetWinCount(int count) {
    winCount = count;
}

int Upgrades::GetWinCount() const{
    return winCount;
}

void Upgrades::DrawPopup(const char* text) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int textWidth = MeasureText(text, 20);
    int textX = (screenWidth - textWidth) / 2;
    int textY = screenHeight / 2;

    DrawRectangle(textX - 10, textY - 10, textWidth + 20, 40, Fade(BLACK, 0.8f));
    DrawText(text, textX, textY, 20, WHITE);
}

void Upgrades::DrawTextInButton(const char* text, Rectangle button) {
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);

    // Adjust font size if text is too wide for the button
    while (textWidth > button.width - 20 && fontSize > 10) {
        fontSize--;
        textWidth = MeasureText(text, fontSize);
    }

    int textX = button.x + (button.width - textWidth) / 2;
    int textY = button.y + (button.height - fontSize) / 2;

    DrawText(text, textX, textY, fontSize, BLACK);
}

void Upgrades::ResetUpgrades() {
    for (auto& button : buttons) {
        button.requiredCookies = button.initalRequiredCookies;
    }
}

void Upgrades::SetCurrentLevel(int level) {
    currentLevel = level;
}

int Upgrades::GetCurrentLevel() const {
    return currentLevel;
}