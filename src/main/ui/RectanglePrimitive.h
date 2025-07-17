#pragma once
#include "Drawable.h"
#include "SFML/Graphics/Color.hpp"


namespace ui {
    class RectanglePrimitive : public Drawable{

    public:

        RectanglePrimitive(float x, float y, float width, float height);

        void setColor(float r, float g, float b, float a);

        void draw() const override;

    private:
        float m_x, m_y, m_width, m_height;
        float m_r = 1.0f, m_g = 1.0f, m_b = 1.0f, m_a = 1.0f;

    };
}



