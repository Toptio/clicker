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
        int btnState;
        bool btnClicked;
        bool showPopup;
        float popupTimer;

        void CheckButtonClicked(Cookie& cookie);
        void DrawPopup();
};

#endif