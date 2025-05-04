#include <raylib.h>
#include "headers/cursor.hpp"

Cursor::Cursor() {
    normaltexture = LoadTexture("assets/cursors/cursor.png");
    clicktexture = LoadTexture("assets/cursors/cursor2.png"); 
}

Cursor::~Cursor() {
    UnloadTexture(normaltexture);
    UnloadTexture(clicktexture);
}

void Cursor::Update(Vector2 mousePoint){}

void Cursor::Draw(Vector2 mousePoint) {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        DrawTexture(clicktexture, mousePoint.x, mousePoint.y, WHITE);
    } else {
        DrawTexture(normaltexture, mousePoint.x, mousePoint.y, WHITE);
    }
}