#pragma once

#include "ButtonBar.h"
#include "TextureMaker.h"

class OldWindow;

class AppUI {
public:
    AppUI(OldWindow& window, const sf::Vector2f& spriteScale, Theme theme);


    std::unique_ptr<ButtonBar> m_menuBar;
    std::unique_ptr<OldButton> m_exitButton;
    std::unique_ptr<OldButton> m_maxButton;
    std::unique_ptr<OldButton> m_minButton;
    std::unique_ptr<sf::Sprite> m_sprite;
    sf::Texture m_texture;

private:
    OldWindow& m_window;
    sf::Font m_font;

    Theme m_theme;

    void centerSprite() const;
};

