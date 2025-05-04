#include <raylib.h>
#include "headers/cookie.hpp"

Cookie::Cookie() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    cookie = LoadTexture("assets/cookies/perfectCookie.png");
    clickSound = LoadSound("assets/sound/click.mp3");

    width = 150;
    height = 150;
    radius = 50;

    cookieCount = 0;
    cookiePerClick = 1;
    cookiePerSecond = 0;
    cookieClicked = false;
    cookieState = 0;
    timer = 0.0f;
}

Cookie::~Cookie() {
    UnloadTexture(cookie);
    UnloadSound(clickSound);
}

void Cookie::Draw() {
    Rectangle source = { 0.0f, 0.0f, (float)cookie.width, (float)cookie.height };
    Rectangle dest = { x, y, width, height };
    Vector2 origin = { width / 2, height / 2 };
    DrawTexturePro(cookie, source, dest, origin, 0.0f, WHITE);
}

void Cookie::Update() {
    Vector2 mousePoint = GetMousePosition();
    if(CheckCollisionPointCircle(mousePoint, {x, y}, radius)) {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            cookieState = 2; // Pressed
            if(!cookieClicked) {
                cookieClicked = true;
                //TraceLog(LOG_INFO, "Cookie Clicked");
            }
        } else {
            cookieState = 1; // Hover
        }
    } else {
        cookieState = 0;
    }

    if(cookieClicked == true && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        cookieCount += cookiePerClick;
        cookieClicked = false;
        PlaySound(clickSound);
    }

    // Update cookie per second
    timer += GetFrameTime();
    if (timer >= 1.0f) {
        cookieCount += cookiePerSecond;
        timer = 0.0f;
    }
}

void Cookie::SetCookieCount(int count) {
    cookieCount = count;
}

int Cookie::GetCookieCount() const {
    return cookieCount;
}

void Cookie::SetCookiePerClick(int count) {
    cookiePerClick = count;
}

int Cookie::GetCookiePerClick() const {
    return cookiePerClick;
}

void Cookie::SetCookiePerSecond(int count) {
    cookiePerSecond = count;
}

int Cookie::GetCookiePerSecond() const {
    return cookiePerSecond;
}

void Cookie::Reset() {
    cookieCount = 0;
    cookiePerClick = 1;
    cookiePerSecond = 0;
}