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
};

Vec2f normalize(const Vec2f& v);

float distance(const Vec2f& a, const Vec2f& b);
