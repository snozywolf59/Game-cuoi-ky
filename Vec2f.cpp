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

Vec2f normalize(const Vec2f& v)
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

float Vec2f::length()
{
    return sqrtf(powf(x,2) + powf(y,2));
}


float distance(const Vec2f& a, const Vec2f& b)
{
    return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
}


