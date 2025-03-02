#include <raylib.h>
#include <cstring>
#include "headers/game_state.hpp"
#include "headers/upgrades.hpp"
#include "headers/cookie.hpp"

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 40
#define POPUP_DURATION 2.0f

extern GameState gameState;

Upgrades::Upgrades() {
    btnState = 0;
    btnState2 = 0;
    btnState3 = 0;
    btnState4 = 0;
    btnWinState = 0;

    btnClicked = false;
    btnClicked2 = false;
    btnClicked3 = false;
    btnClicked4 = false;
    btnWinClicked = false;

    showPopup = false;
    popupTimer = 0.0f;
    popupText = "";
}

void Upgrades::Draw() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Define panel
    upgradesPanel = { (float)screenWidth - (screenWidth * 0.3f), 0, screenWidth * 0.3f, (float)screenHeight };

    // Define buttons
    button = { (float)screenWidth - (screenWidth * 0.3f) + 10, 50, BUTTON_WIDTH, BUTTON_HEIGHT };
    button2 = { (float)screenWidth - (screenWidth * 0.3f) + 10, 100, BUTTON_WIDTH, BUTTON_HEIGHT };
    button3 = { (float)screenWidth - (screenWidth * 0.3f) + 10, 150, BUTTON_WIDTH, BUTTON_HEIGHT }; 
    button4 = { (float)screenWidth - (screenWidth * 0.3f) + 10, 200, BUTTON_WIDTH, BUTTON_HEIGHT };
    btnWin = { (float)screenWidth - (screenWidth * 0.3f) + 10, 400, BUTTON_WIDTH, BUTTON_HEIGHT };

    // Draw upgrades panel
    DrawRectangleRec(upgradesPanel, Fade(WHITE, 0.5f));
    DrawText("Upgrades", screenWidth - (screenWidth * 0.3f) + 10, 10, 20, WHITE);

    // Draw button
    Color color;
    switch(btnState) {
        case 0: color = RED; break;
        case 1: color = YELLOW; break;
        case 2: color = WHITE; break;
    }

    DrawRectangleRec(button, color);
    DrawTextInButton("+1 cookie per click", button);

    switch(btnState2) {
        case 0: color = RED; break;
        case 1: color = YELLOW; break;
        case 2: color = WHITE; break;
    }

    DrawRectangleRec(button2, color);
    DrawTextInButton("Double cookies per click", button2);

    switch(btnState3) {
        case 0: color = RED; break;
        case 1: color = YELLOW; break;
        case 2: color = WHITE; break;
    }

    DrawRectangleRec(button3, color);
    DrawTextInButton("+1 cookie per second", button3);

    switch(btnState4) {
        case 0: color = RED; break;
        case 1: color = YELLOW; break;
        case 2: color = WHITE; break;
    }

    DrawRectangleRec(button4, color);
    DrawTextInButton("+4 cookiesper second", button4);

    switch(btnWinState) {
        case 0: color = RED; break;
        case 1: color = YELLOW; break;
        case 2: color = WHITE; break;
    }

    DrawRectangleRec(btnWin, color);
    DrawTextInButton("Win button", btnWin);

    // Draw popup if visible
    if (showPopup) {
        DrawPopup(popupText);
    }
}

void Upgrades::Update(Cookie& cookie) {

    HandleButton(button, btnState, btnClicked, cookie, 50, "click", 1);
    HandleButton(button2, btnState2, btnClicked2, cookie, 500, "click", cookie.GetCookiePerClick());
    HandleButton(button3, btnState3, btnClicked3, cookie, 200, "second", 1);
    HandleButton(button4, btnState4, btnClicked4, cookie, 400, "second", 10);
    HandleButton(btnWin, btnWinState, btnWinClicked, cookie, 1000000, "win", 0);

    // Update popup timer
    if (showPopup) {
        popupTimer -= GetFrameTime();
        if (popupTimer <= 0.0f) {
            showPopup = false;
        }
    }
}

void Upgrades::HandleButton(Rectangle button, int& btnState, bool& btnClicked, Cookie& cookie, int requiredCookies, const char* upgradeType, int upgradeAmount) {
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, button)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            btnState = 2; // Pressed
            if (!btnClicked) {
                btnClicked = true;
                CheckButtonClicked(cookie, requiredCookies, upgradeType, upgradeAmount);
            }
        } else {
            btnState = 1; // Hover
        }
    } else {
        btnState = 0; // Normal
    }

    if (btnClicked && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        btnClicked = false;
    }
}

void Upgrades::CheckButtonClicked(Cookie& cookie, int requiredCookies, const char* upgradeType, int upgradeAmount) {
    if (cookie.GetCookieCount() >= requiredCookies) {
        cookie.SetCookieCount(cookie.GetCookieCount() - requiredCookies);
        if (strcmp(upgradeType, "click") == 0) {
            cookie.SetCookiePerClick(cookie.GetCookiePerClick() + upgradeAmount);
            TraceLog(LOG_INFO, "Cookie per click is now: %d", cookie.GetCookiePerClick());
        } else if (strcmp(upgradeType, "second") == 0) {
            cookie.SetCookiePerSecond(cookie.GetCookiePerSecond() + upgradeAmount);
            TraceLog(LOG_INFO, "Cookie per second is now: %d", cookie.GetCookiePerSecond());
        } else if (strcmp(upgradeType, "win") == 0) {
            cookie.reset();
            gameState = GameState::WIN;
        }
    } else {
        TraceLog(LOG_INFO, "Not enough cookies: %d", cookie.GetCookieCount());
        TraceLog(LOG_INFO, "Need %d cookies to buy upgrade", requiredCookies);
        popupText = TextFormat("Not enough cookies! Need %d cookies to buy upgrade", requiredCookies);
        showPopup = true; // Show popup
        popupTimer = POPUP_DURATION; // Reset popup timer
    }
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