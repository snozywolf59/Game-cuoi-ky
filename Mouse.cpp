#include "Mouse.h"

Mouse::Mouse(SDL_Renderer* _renderer, const string& path)
{
    renderer = _renderer;
    loadEntity(path);
}


    //MOUSE
void Mouse::updateMouse(const Vec2f& camera)
{
    x = camera.x + real_mouse_x;
    y = camera.y + real_mouse_y;
    now = (now + 1)%16;
}

