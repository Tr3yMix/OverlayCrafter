#pragma once

#include <string>

#include "Drawable.h"
#include "math/Vector2.h"
#include "oldsfml/App.h"
#include "util/Color.h"


#include <GL/gl.h>

namespace ui {

    class Text : public Drawable{

    public:
        Text(const std::string& text, math::Vector2f position, const util::Color& color = util::Color(0xfff));
        ~Text() override = default;

        void draw(const DrawTarget& target) const override;

        void setText(const std::string& text);
        void setPosition(const math::Vector2f& position);
        void setColor(const util::Color& color);

        static void InitFont(HDC hdc);
        static void CleanupFont();

    private:

        std::string m_text;
        math::Vector2f m_position;
        util::Color m_color;

        static GLuint s_fontBase;
        static bool s_isFontInitialized;


    };

} // ui

