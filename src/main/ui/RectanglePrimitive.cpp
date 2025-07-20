#include "RectanglePrimitive.h"

#include <GL/gl.h>

#include "DrawTarget.h"
#include "math/Vector2.h"


namespace ui {
    RectanglePrimitive::RectanglePrimitive(const math::Vector2f position, const float width, const float height):
    m_position(position), m_width(width), m_height(height) {}

    void RectanglePrimitive::setColor(const util::Color& color) {
        m_r = color.rF();
        m_g = color.gF();
        m_b = color.bF();
        m_a = color.aF();
    }

    void RectanglePrimitive::draw(const DrawTarget& target) const {

        const GLfloat glX = m_position.xNDC();
        const GLfloat glY = m_position.yNDC();

        const GLfloat glWidth = m_width / static_cast<float>(target.getWidth()) * 2.0f;
        const GLfloat glHeight = -(m_height / static_cast<float>(target.getHeight()) * 2.0f);

        glBegin(GL_QUADS);
            glColor4f(m_r, m_g, m_b, m_a);
            glVertex2f(glX, glY);
            glVertex2f(glX + glWidth, glY);
            glVertex2f(glX + glWidth, glY + glHeight);
            glVertex2f(glX, glY + glHeight);
        glEnd();
    }

}






