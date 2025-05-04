#ifndef UPGRADES_HPP
#define UPGRADES_HPP

#include <raylib.h>
#include <vector>
#include "cookie.hpp"

class Upgrades {
    public:
        Upgrades();
        void Draw();
        void Draw2();
        void Update(Cookie& cookie);

        void SetRequiredCookies(int index, int requiredCookies);
        int GetRequiredCookies(int index) const;
        void SetWinCount(int count);
        int GetWinCount() const;
        void SetCurrentLevel(int level);
        int GetCurrentLevel() const;

        void ResetUpgrades();
    private:
        struct Button {
            Rectangle rect;
            int state;
            bool clicked;
            const char* text;
            int requiredCookies;
            const char* upgradeType;
            int upgradeAmount;
            int initalRequiredCookies;
            float priceMultiplier = 1.15f;
            bool purchased;
        };

        Rectangle upgradesPanel;
        std::vector<Button> buttons;
        int winCount;
        int currentLevel;
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