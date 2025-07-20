#include "AppUI.h"

#include "RectanglePrimitive.h"
#include "Text.h"

namespace ui {

    AppUI::AppUI(AppWindow* window): m_window(window) {

        Text::InitFont(m_window->m_hdc);

        m_text = std::make_unique<Text>("Hello World!", math::Vector2f(.5, .5), util::Color(0xfff));

        m_topBar = std::make_unique<RectanglePrimitive>(math::Vector2f(0, 0), static_cast<float>(m_window->getWidth()), 40);

        m_topBar->setColor(util::Color(0x333));

        const float x = (static_cast<float>(m_window->getWidth()) - 40) / static_cast<float>(m_window->getWidth());

        m_exitButton = std::make_unique<RectanglePrimitive>(math::Vector2f(x, 0), 40, 40);

        m_exitButton->setColor(util::Color(0xfff));
        
    }


    void AppUI::draw() const {
        
        m_window->clear(util::Color(0x222));

        m_window->draw(*m_topBar);
        m_window->draw(*m_exitButton);
        m_window->draw(*m_text);
    }
    
} // ui