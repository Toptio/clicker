#include <raylib.h>
#include "headers/upgrades.hpp"

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 40
#define POPUP_DURATION 2.0f

Upgrades::Upgrades() {

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    btnState = 0;
    btnClicked = false;
    showPopup = false;
    popupTimer = 0.0f;

    // Define panel
    upgradesPanel = { (float)screenWidth - 240, 0, 240, (float)screenHeight };

    // Define button
    button = { (float)screenWidth - 230, 50, BUTTON_WIDTH, BUTTON_HEIGHT };}

void Upgrades::Draw() {
    int screenWidth = GetScreenWidth();

    // Draw upgrades panel
    DrawRectangleRec(upgradesPanel, Fade(WHITE, 0.5f));
    DrawText("Upgrades", screenWidth - 230, 10, 20, WHITE);
    
    // Draw button
    Color color;
    switch(btnState) {
        case 0: color = RED; break;
        case 1: color = YELLOW; break;
        case 2: color = WHITE; break;
    }

    DrawRectangleRec(button, color);
    DrawText("Buy, +1 cookie", button.x + 10, button.y + 10, 20, BLACK);
}

void Upgrades::Update(Cookie& cookie) {
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, button)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            btnState = 2; // Pressed
            if (!btnClicked) {
                btnClicked = true;
                TraceLog(LOG_INFO, "Button Clicked");
            }
        } else {
            btnState = 1; // Hover
        }
    } else {
        btnState = 0; // Normal
    }

    if (btnClicked && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        CheckButtonClicked(cookie);
        btnClicked = false;
    }

    if (showPopup) {
        DrawPopup();
        popupTimer -= GetFrameTime();
        if (popupTimer <= 0.0f) {
            showPopup = false;
        }
    }
}

void Upgrades::CheckButtonClicked(Cookie& cookie) {
    if (cookie.GetCookieCount() >= 10) {
        cookie.SetCookieCount(cookie.GetCookieCount() - 10);
        cookie.SetCookiePerClick(cookie.GetCookiePerClick() + 1);
    } else {
        TraceLog(LOG_INFO, "Not enough cookies: %d", cookie.GetCookieCount());
        TraceLog(LOG_INFO, "Need 10 cookies to buy upgrade");
        showPopup = true; // Show popup
        popupTimer = POPUP_DURATION; // Reset popup timer
    }
}

void Upgrades::DrawPopup() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    const char* message = "Not enough cookies! Need 10 cookies to buy upgrade.";
    int textWidth = MeasureText(message, 20);
    int textX = (screenWidth - textWidth) / 2;
    int textY = screenHeight / 2;

    DrawRectangle(textX - 10, textY - 10, textWidth + 20, 40, Fade(BLACK, 0.8f));
    DrawText(message, textX, textY, 20, WHITE);
}