#include "Vec2f.h"

Vec2f::Vec2f()
{
    x = 0;
    y = 0;
}

Vec2f::Vec2f(float x_, float y_)
{
    x = x_;
    y = y_;
}

Vec2f Vec2f::operator+(const Vec2f& other) const
{
    return Vec2f(x + other.x, y + other.y);
}

Vec2f Vec2f::operator-(const Vec2f& other) const
{
    return Vec2f(x - other.x, y - other.y);
}

Vec2f Vec2f::operator*(const float& scalar) const
{
    return Vec2f(x * scalar, y * scalar);
}

Vec2f Vec2f::operator/(const float& scalar) const
{
    return Vec2f(x / scalar, y / scalar);
}

Vec2f& Vec2f::operator*=(const float& scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2f& Vec2f::operator/=(const float& scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

Vec2f& Vec2f::operator+=(const Vec2f& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vec2f& Vec2f::operator-=(const Vec2f& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

void Vec2f::normalize()
{
    float mag = length();
    if (mag != 0){
        x /= mag;
        y /= mag;
    }
}

float Vec2f::length()
{
    return sqrtf(powf(x,2) + powf(y,2));
}

Vec2f normal(const Vec2f& v)
{
    float len = sqrtf(powf(v.x, 2) + powf(v.y, 2));
        if (len > 0.0f)
        {
            return v / len;
        }
        else
        {
            return Vec2f(0.0f, 0.0f);
        }
}



float distance(const Vec2f& a, const Vec2f& b)
{
    return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
}
Vec2f Rotate(const float& angle, const Vec2f& v)
{
    float cosA = cosf(angle);
    float sinA = sinf(angle);
    float x = v.x*cosA - v.y*sinA;
    float y = v.x*sinA + v.y*cosA;
    return {x, y};
}

float tangent(const Vec2f& m, const Vec2f& c, const float& r)
{
    return atan2(r, (m-c).length());
}


void drawCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
    for (int w = 0; w < radius * 2; ++w) {
        for (int h = 0; h < radius * 2; ++h) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

