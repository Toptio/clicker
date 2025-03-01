#ifndef UPGRADES_HPP
#define UPGRADES_HPP

#include <raylib.h>
#include "cookie.hpp"

class Upgrades {
    public:
        Upgrades();
        void Draw();
        void Update(Cookie& cookie);
    private:
        Rectangle upgradesPanel;
        Rectangle button;
        Rectangle button2;
        Rectangle button3;
        Rectangle btnWin;
        int btnState;
        int btnState2;
        int btnState3;
        int btnWinState;
        bool btnClicked;
        bool btnClicked2;
        bool btnClicked3;
        bool btnWinClicked;
        bool showPopup;
        float popupTimer;
        const char* popupText;

        void CheckButtonClicked(Cookie& cookie);
        void CheckButtonDoubleClicked(Cookie& cookie);
        void CheckAutoButtonClicked(Cookie& cookie);
        void CheckButtonWin(Cookie& cookie);
        void DrawPopup(const char* text);
        void DrawTextInButton(const char* text, Rectangle button);
};

#endif