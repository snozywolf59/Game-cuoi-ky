#pragma once

#include "Entity.h"

struct Mouse:Entity
{
    int real_mouse_x, real_mouse_y, now = 0;

    Mouse(SDL_Renderer* _renderer, const string& path);

    void updateMouse(const Vec2f& camera);
};
