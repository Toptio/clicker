#include <raylib.h>
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
    btnWinState = 0;

    btnClicked = false;
    btnClicked2 = false;
    btnClicked3 = false;
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
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, button)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            btnState = 2; // Pressed
            if (!btnClicked) {
                btnClicked = true;
                //TraceLog(LOG_INFO, "Button Clicked");
                CheckButtonClicked(cookie);
            }
        } else {
            btnState = 1; // Hover
        }
    } else {
        btnState = 0; // Normal
    }

    if (CheckCollisionPointRec(mousePoint, button2)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            btnState2 = 2; // Pressed
            if (!btnClicked2) {
                btnClicked2 = true;
                //TraceLog(LOG_INFO, "Double Button Clicked");
                CheckButtonDoubleClicked(cookie);
            }
        } else {
            btnState2 = 1; // Hover
        }
    } else {
        btnState2 = 0; // Normal
    }

    if (CheckCollisionPointRec(mousePoint, button3)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            btnState3 = 2; // Pressed
            if (!btnClicked3) {
                btnClicked3 = true;
                //TraceLog(LOG_INFO, "Button Clicked");
                CheckAutoButtonClicked(cookie);
            }
        } else {
            btnState3 = 1; // Hover
        }
    } else {
        btnState3 = 0; // Normal
    }

    if (CheckCollisionPointRec(mousePoint, btnWin)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            btnWinState = 2; // Pressed
            if (!btnWinClicked) {
                btnWinClicked = true;
                TraceLog(LOG_INFO, "Win Button Clicked");
                CheckButtonWin(cookie);
            }
        } else {
            btnWinState = 1; // Hover
        }
    } else {
        btnWinState = 0; // Normal
    }

    if (btnClicked && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        btnClicked = false;
    }

    if (btnClicked2 && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        btnClicked2 = false;
    }

    if (btnClicked3 && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        btnClicked3 = false;
    }

    if (btnWinClicked && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        btnWinClicked = false;
    }

    // Update popup timer
    if (showPopup) {
        popupTimer -= GetFrameTime();
        if (popupTimer <= 0.0f) {
            showPopup = false;
        }
    }
}

void Upgrades::CheckButtonClicked(Cookie& cookie) {
    if (cookie.GetCookieCount() >= 100) {
        cookie.SetCookieCount(cookie.GetCookieCount() - 100);
        cookie.SetCookiePerClick(cookie.GetCookiePerClick() + 1);
        TraceLog(LOG_INFO, "Cookie per click is now: %d", cookie.GetCookiePerClick());
    } else {
        TraceLog(LOG_INFO, "Not enough cookies: %d", cookie.GetCookieCount());
        TraceLog(LOG_INFO, "Need 100 cookies to buy upgrade");
        popupText = "Not enough cookies! Need 100 cookies to buy upgrade";
        showPopup = true; // Show popup
        popupTimer = POPUP_DURATION; // Reset popup timer
    }
}

void Upgrades::CheckButtonDoubleClicked(Cookie& cookie) {
    if (cookie.GetCookieCount() >= 500) {
        cookie.SetCookieCount(cookie.GetCookieCount() - 500);
        cookie.SetCookiePerClick(cookie.GetCookiePerClick() * 2);
        TraceLog(LOG_INFO, "Cookie per click is now: %d", cookie.GetCookiePerClick());
    } else {
        TraceLog(LOG_INFO, "Not enough cookies: %d", cookie.GetCookieCount());
        TraceLog(LOG_INFO, "Need 500 cookies to buy upgrade");
        popupText = "Not enough cookies! Need 500 cookies to buy upgrade";
        showPopup = true; // Show popup
        popupTimer = POPUP_DURATION; // Reset popup timer
    }
}

void Upgrades::CheckAutoButtonClicked(Cookie& cookie) {
    if (cookie.GetCookieCount() >= 200) {
        cookie.SetCookieCount(cookie.GetCookieCount() - 200);
        cookie.SetCookiePerSecond(cookie.GetCookiePerSecond() + 1);
        TraceLog(LOG_INFO, "Cookie per second is now: %d", cookie.GetCookiePerSecond());
    } else {
        TraceLog(LOG_INFO, "Not enough cookies: %d", cookie.GetCookieCount());
        TraceLog(LOG_INFO, "Need 200 cookies to buy upgrade");
        popupText = "Not enough cookies! Need 200 cookies to buy upgrade";
        showPopup = true; // Show popup
        popupTimer = POPUP_DURATION; // Reset popup timer
    }
}

void Upgrades::CheckButtonWin(Cookie& cookie) {
    if (cookie.GetCookieCount() >= 1000000) {
        cookie.reset();
        gameState = GameState::WIN;
    } else {
        TraceLog(LOG_INFO, "Not enough cookies: %d", cookie.GetCookieCount());
        TraceLog(LOG_INFO, "Need 1000000 cookies to buy upgrade");
        popupText = "Not enough cookies! Need 1M cookies to buy upgrade";
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