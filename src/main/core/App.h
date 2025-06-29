#pragma once

#include "Common.h"

#include "SFML/Graphics.hpp"

#include "ui/Button.h"
#include "ui/Toolbar.h"
#include "utils/Theme.h"


class App {

public:
    App(std::string  title, sf::Vector2<float> windowDimensions, sf::Vector2<float> spriteScale, Theme  theme);
    App();

    //Functions
    void update();

    sf::RenderWindow m_window;

private:

    //Window Properties
    std::string m_title;
    sf::Vector2<float> m_windowDimensions;

    //Image Texture Properties
    sf::Vector2<float> m_spriteScale;

    //Color
    //sf::Color m_backgroundColor;
    Theme m_theme;

    std::unique_ptr<Toolbar> m_toolbar;

    std::unique_ptr<sf::View> m_view;
    sf::Texture m_imageTexture;
    sf::Font m_font;
    std::unique_ptr<sf::Sprite> m_sprite;

    //Functions
    void initWindow();
    void initView();
    void initFont();
    void initToolbar();
    void initSprite();

    void centerSprite() const;

    void handleEvents();
    void updateViewAspectRatio(const sf::Event::Resized& event);

};

