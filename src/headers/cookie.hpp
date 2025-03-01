#ifndef COOKIE_HPP
#define COOKIE_HPP

#include <raylib.h>

class Cookie {
    public:
        Cookie();
        ~Cookie();
        void Draw();
        void Update();
        int GetCookieCount() const;
        void SetCookieCount(int count); 
        int GetCookiePerClick() const;
        void SetCookiePerClick(int count);
    private:
        float x, y;
        float width, height,radius;
        int cookiePerClick;
        int cookieCount;
        int cookieState;
        bool cookieClicked;
        Sound clickSound;
        Texture2D cookie;
        Texture2D cookieHover;
};

#endif