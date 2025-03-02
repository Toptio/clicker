#ifndef UPGRADES_HPP
#define UPGRADES_HPP

#include <raylib.h>
#include <vector>
#include "cookie.hpp"

class Upgrades {
    public:
        Upgrades();
        void Draw();
        void Update(Cookie& cookie);
        void SetRequiredCookies(int index, int requiredCookies);
        int GetRequiredCookies(int index) const;
    private:
        struct Button {
            Rectangle rect;
            int state;
            bool clicked;
            const char* text;
            int requiredCookies;
            const char* upgradeType;
            int upgradeAmount;
            float priceMultiplier = 1.15f;
        };

        Rectangle upgradesPanel;
        std::vector<Button> buttons;
        bool showPopup;
        float popupTimer;
        const char* popupText;

        void UpdateButtonsPositions();
        void HandleButton(Button& button, Cookie& cookie);
        void CheckButtonClicked(Button& button, Cookie& cookie);
        void DrawPopup(const char* text);
        void DrawTextInButton(const char* text, Rectangle button);
};

#endif