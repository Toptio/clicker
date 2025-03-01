#include <raylib.h>

class Menu {
    public:
        Menu();
        ~Menu();
        void Draw();
        void Update();
    private:
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        const char* text = "Press Enter to start the game";
        int textWidth = MeasureText("Press Enter to Start", 20);
        int textX = (screenWidth - textWidth) / 2;
        int textY = screenHeight / 2;
};