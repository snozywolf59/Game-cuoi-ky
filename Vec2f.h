#pragma once

#include "common.h"

struct Vec2f
{
    float x, y;

    Vec2f();
    Vec2f(float x_, float y_);

    Vec2f operator+(const Vec2f& other) const;

    Vec2f operator-(const Vec2f& other) const;

    Vec2f operator*(const float& scalar) const;

    Vec2f operator/(const float& scalar) const;

    Vec2f& operator*=(const float& scalar);

    Vec2f& operator/=(const float& scalar);

    Vec2f& operator+=(const Vec2f& other);

    Vec2f& operator-=(const Vec2f& other);

    float length();

    void normalize();
};

Vec2f normal(const Vec2f& v);

Vec2f Rotate(const float& angle, const Vec2f& v);

float distance(const Vec2f& a, const Vec2f& b);

float tangent1(const Vec2f& m, const Vec2f& c, const float& r);
float tangent2(const Vec2f& m, const Vec2f& c, const float& r);

void drawCircle(SDL_Renderer* renderer, int x, int y, int radius);
