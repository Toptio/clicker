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
        Rectangle button4;
        Rectangle btnWin;
        int btnState;
        int btnState2;
        int btnState3;
        int btnState4;
        int btnWinState;
        bool btnClicked;
        bool btnClicked2;
        bool btnClicked3;
        bool btnClicked4;
        bool btnWinClicked;
        bool showPopup;
        float popupTimer;
        const char* popupText;

        void HandleButton(Rectangle button, int& btnState, bool& btnClicked, Cookie& cookie, int requiredCookies, const char* upgradeType, int upgradeAmount);
        void CheckButtonClicked(Cookie& cookie, int requiredCookies, const char* upgradeType, int upgradeAmount);
        void DrawPopup(const char* text);
        void DrawTextInButton(const char* text, Rectangle button);
};

#endif