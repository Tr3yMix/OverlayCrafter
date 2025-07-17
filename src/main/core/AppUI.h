#pragma once

#include "ui/ButtonBar.h"
#include "utils/TextureMaker.h"

class OldWindow;

class AppUI {
public:
    AppUI(OldWindow& window, const sf::Vector2f& spriteScale, Theme theme);


    std::unique_ptr<ButtonBar> m_menuBar;
    std::unique_ptr<Button> m_exitButton;
    std::unique_ptr<Button> m_maxButton;
    std::unique_ptr<Button> m_minButton;
    std::unique_ptr<sf::Sprite> m_sprite;
    sf::Texture m_texture;

private:
    OldWindow& m_window;
    sf::Font m_font;

    Theme m_theme;

    void centerSprite() const;
};

