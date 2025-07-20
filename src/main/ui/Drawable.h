#pragma once

namespace ui {
    class DrawTarget;

    class Drawable {

    public:
        virtual ~Drawable() = default;

        virtual void draw(const DrawTarget& target) const = 0;

        static float toGLX(const float normalized) {
            return normalized * 2.f - 1.f;
        }

        static float toGLY(const float normalized) {
            return -(normalized * 2.f - 1.f);
        }
    };
}
