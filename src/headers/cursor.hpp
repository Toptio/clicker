#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <raylib.h>

class Cursor {
    public:
        Cursor();
        ~Cursor();
        void Update(Vector2 mousePoint);
        void Draw(Vector2 mousePoint);
    private:
        Texture2D normaltexture;
        Texture2D clicktexture;
};

#endif