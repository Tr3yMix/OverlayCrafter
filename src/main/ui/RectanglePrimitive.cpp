#include "RectanglePrimitive.h"

#include <GL/gl.h>

namespace ui {
    RectanglePrimitive::RectanglePrimitive(const float x, const float y, const float width, const float height):
    m_x(x), m_y(y), m_width(width), m_height(height) {}

    void RectanglePrimitive::setColor(const float r, const float g, const float b, const float a) {
        m_r = r;
        m_g = g;
        m_b = b;
        m_a = a;
    }

    void RectanglePrimitive::draw() const {

        glBegin(GL_QUADS);
        glColor4f(m_r, m_g, m_b, m_a);
        glVertex2f(m_x, m_y);
        glVertex2f(m_x + m_width, m_y);
        glVertex2f(m_x + m_width, m_y + m_height);
        glVertex2f(m_x, m_y + m_height);
        glEnd();
    }

}






