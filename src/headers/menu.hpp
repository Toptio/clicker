#ifndef MENU_HPP
#define MENU_HPP

#pragma once
#include <raylib.h>

class Menu {
    public:
        Menu();
        ~Menu();
        void Draw();
        void Update();
    private:    
        Rectangle startButton;
        Color buttonColor;
        Color buttonHoverColor;
        bool isButtonHovered;
        const char* buttonText;

        Rectangle optionsButton;
        Color optionsButtonColor;
        Color optionsButtonHoverColor;
        bool isOptionsButtonHovered;
        const char* optionsButtonText;
};

#endif 