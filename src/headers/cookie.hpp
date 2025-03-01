#ifndef COOKIE_HPP
#define COOKIE_HPP

#include <raylib.h>

class Cookie {
    public:
        Cookie();
        ~Cookie();
        void Draw();
        void Update();
        void SetCookieCount(int count); 
        int GetCookieCount() const;
        void SetCookiePerClick(int count);
        int GetCookiePerClick() const;
        void SetCookiePerSecond(int count);
        int GetCookiePerSecond() const;
        void reset();
    private:
        float x, y;
        float width, height,radius;
        int cookieState;
        int cookieCount;
        int cookiePerClick;
        int cookiePerSecond;
        bool cookieClicked;
        float timer;

        Sound clickSound;
        Texture2D cookie;
        Texture2D cookieHover;
};

#endif