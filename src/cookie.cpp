#include <raylib.h>
#include "headers/cookie.hpp"

Cookie::Cookie() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;
    cookie = LoadTexture("assets/cookies/perfectCookie.png");
    clickSound = LoadSound("assets/sound/click.mp3");
    width = 100;
    height = 100;
    radius = 50;
    cookieCount = 0;
    cookieClicked = false;
    cookieState = 0;
}

Cookie::~Cookie() {
    UnloadTexture(cookie);
    UnloadSound(clickSound);
}

void Cookie::Draw() {
   /* Color color;
    switch(cookieState){
        case 0:
            color = WHITE;
            break;
        case 1:
            color = YELLOW;
            break;
        case 2:
            color = RED;
            break;
    } 
    DrawCircle(x, y, radius, color); */

    Rectangle source = { 0.0f, 0.0f, (float)cookie.width, (float)cookie.height };
    Rectangle dest = { x, y, width, height };
    Vector2 origin = { width / 2, height / 2 };
    DrawTexturePro(cookie, source, dest, origin, 0.0f, WHITE);
}

void Cookie::Update() {
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointCircle(mousePoint, {x, y}, radius)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            cookieState = 2; // Pressed
            cookieClicked = true;
        } else {
            cookieState = 1; // Hover
        }
    } else {
        cookieState = 0;
    }

    if(cookieClicked == true && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        cookieCount++;
        cookieClicked = false;
        PlaySound(clickSound);
    }
}

int Cookie::GetCookieCount() const {
    return cookieCount;
}

void Cookie::SetCookieCount(int count) {
    cookieCount = count;
}

