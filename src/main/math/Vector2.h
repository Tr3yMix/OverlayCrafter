#pragma once

namespace math {
    struct Vector2f {

        float x, y;

        Vector2f(const float x, const float y) : x(x), y(y) {}

        [[nodiscard]] float xNDC() const {return x * 2.f - 1.f;}
        [[nodiscard]] float yNDC() const {return -(y * 2.f - 1.f);}

    };

    struct Vector2u {

        unsigned int x, y;

        Vector2u(const unsigned int x, const unsigned int y) : x(x), y(y) {}

        [[nodiscard]] signed int signedX() const {return static_cast<signed int>(x);}
        [[nodiscard]] signed int signedY() const {return static_cast<signed int>(y);}

    };
}


