#include "Text.h"

#include "DrawTarget.h"

namespace ui {

    GLuint Text::s_fontBase = 0;
    bool Text::s_isFontInitialized = false;

    Text::Text(const std::string &text, const math::Vector2f position, const util::Color &color): m_text(text), m_position(position), m_color(color) {}

    void Text::InitFont(const HDC hdc) {
        if (s_isFontInitialized) return;

        const HFONT font = CreateFontA(
            -18, 0, 0, 0,
            FW_NORMAL,
            FALSE, FALSE, FALSE,
            ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
            ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Consolas"
            );

        SelectObject(hdc, font);

        s_fontBase = glGenLists(96);
        wglUseFontBitmapsA(hdc, 32, 96, s_fontBase);

        s_isFontInitialized = true;
    }

    void Text::CleanupFont() {
        if (!s_isFontInitialized) return;

        glDeleteLists(s_fontBase, 96);
        s_isFontInitialized = false;
    }

    void Text::draw(const DrawTarget& target) const {
        if (!s_isFontInitialized) return;

        glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, target.getWidth(), 0, target.getHeight(), -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glColor3f(m_color.rF(), m_color.gF(), m_color.bF());

        const float pixelX = m_position.x * target.getWidth();
        const float pixelY = (1.0f - m_position.y) * target.getHeight();

        glRasterPos2f(pixelX, pixelY);
        glListBase(s_fontBase - 32);
        glCallLists(m_text.size(), GL_UNSIGNED_BYTE, m_text.c_str());

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopAttrib();
    }

    void Text::setText(const std::string &text) {
        m_text = text;
    }

    void Text::setPosition(const math::Vector2f &position) {
        m_position = position;
    }

    void Text::setColor(const util::Color &color) {
        m_color = color;
    }




}
