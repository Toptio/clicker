#ifndef COOKIE_HPP
#define COOKIE_HPP

#include <raylib.h>

class Cookie {
    public:
        Cookie();
        ~Cookie();
        void Draw();
        void Update();
        int GetCookieState() const;
        int GetCookieCount() const;
        void SetCookieCount(int count);

    private:
        float x, y;
        float width, height,radius;
        int cookieCount;
        int cookieState;
        bool cookieClicked;
        Sound clickSound;
        Texture2D texture;
};

#endif