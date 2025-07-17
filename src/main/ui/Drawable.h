#pragma once

namespace ui {
    class Drawable {
        public:
        virtual ~Drawable() = default;

        virtual void draw() const = 0;
    };
}
