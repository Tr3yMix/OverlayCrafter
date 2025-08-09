#pragma once
#include <iostream>
#include <cmath>

#include "Uint.h"

namespace math {

    struct Vector2f {

        float x, y;

        Vector2f(const float x, const float y) : x(x), y(y) {}

        //Arithmetic operators

        constexpr Vector2f operator+(const Vector2f& other) const noexcept {
            return {x + other.x, y + other.y};
        }
        constexpr Vector2f operator-(const Vector2f& other) const noexcept {
            return {x - other.x, y - other.y};
        }
        constexpr Vector2f operator*(const float scalar) const noexcept {
            return {x * scalar, y * scalar};
        }
        constexpr Vector2f operator/(const float scalar) const noexcept {
            return {x / scalar, y / scalar};
        }

        //Compound assignments
        Vector2f& operator+=(const Vector2f& other) noexcept {
            x += other.x; y += other.y; return *this;
        }
        Vector2f& operator-=(const Vector2f& other) noexcept {
            x -= other.x; y -= other.y; return *this;
        }
        Vector2f& operator*=(const float scalar) noexcept {
            x *= scalar; y *= scalar; return *this;
        }
        Vector2f& operator/=(const float scalar) noexcept {
            x /= scalar; y /= scalar; return *this;
        }

        // Equality
        constexpr bool operator==(const Vector2f& other) const noexcept {
            return x == other.x && y == other.y;
        }
        constexpr bool operator!=(const Vector2f& other) const noexcept {
            return !(*this == other);
        }

        //Vector operations

        /*
        [[nodiscard]] constexpr float dot(const Vector2f& other) const noexcept {
            return x * other.x + y * other.y;
        }

        [[nodiscard]] float length() const noexcept {
            return std::sqrt(x * x + y * y);
        }

        [[nodiscard]] Vector2f normalized() const noexcept {
            const float length = length();
            if (length == 0.f) return {0.f, 0.f};
            return *this / length;
        }

        */

        [[nodiscard]] constexpr float xNDC() const {return x * 2.f - 1.f;}
        [[nodiscard]] constexpr float yNDC() const {return -(y * 2.f - 1.f);}

        friend std::ostream& operator<<(std::ostream& os, const Vector2f& v) {
            return os << "(" << v.x << ", " << v.y << ")";
        }


    };

    struct Vector2u {

        Uint x, y;

        constexpr Vector2u(const Uint x, const Uint y): x(x), y(y) {}
        constexpr Vector2u(const unsigned int x, const unsigned int y): x(Uint(x)), y(Uint(y)) {}
        constexpr Vector2u(const int x, const int y): x(Uint(x)), y(Uint(y)) {}

        [[nodiscard]] signed int signedX() const {return x.signedInt();}
        [[nodiscard]] signed int signedY() const {return y.signedInt();}

        //Arithmetic Operators

        constexpr Vector2u operator+(const Vector2u& other) const noexcept {
            return {x + other.x, y + other.y};
        }
        constexpr Vector2u operator-(const Vector2u& other) const noexcept {
            return {x - other.x, y - other.y};
        }


        //Compound Assignments
        Vector2u& operator+=(const Vector2u& other) noexcept {
            x += other.x; y += other.y; return *this;
        }
        Vector2u& operator-=(const Vector2u& other) noexcept {
            x -= other.x; y -= other.y; return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector2u& v) {
            return os << "(" << v.x << ", " << v.y << ")";
        }

    };
}


