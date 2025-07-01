#pragma once


#include "platform/windows/DragAndDropHandler.h"
#include "SFML/Graphics.hpp"

#include "ui/Button.h"
#include "ui/MenuBar.h"
#include "utils/Theme.h"


class App {

public:
    App(std::string  title, sf::Vector2<float> windowDimensions, sf::Vector2<float> spriteScale, Theme  theme);
    App();

    //Functions
    void update();

    sf::RenderWindow m_window;

private:

    bool m_draggingWindow = false;
    POINT m_dragMouseStartPos{};
    POINT m_dragWindowStartPos{};

    std::unique_ptr<DragAndDropHandler> m_dragHandler;

    //Window Properties
    std::string m_title;
    sf::Vector2<float> m_initWindowSize;

    //Image Texture Properties
    sf::Vector2<float> m_spriteScale;

    //Color
    //sf::Color m_backgroundColor;
    Theme m_theme;

    std::unique_ptr<MenuBar> m_menubar;
    std::unique_ptr<Button> m_button;
    float m_menuBarWidth = 120;

    std::unique_ptr<sf::View> m_mainView;
    std::unique_ptr<sf::View> m_topView;
    std::unique_ptr<sf::View> m_leftView;
    std::unique_ptr<sf::View> m_rightView;
    sf::Texture m_imageTexture;
    sf::Font m_font;
    std::unique_ptr<sf::Sprite> m_sprite;

    //Functions
    void initWindow();
    void initViews();
    void initFont();
    void initToolbar();
    void initSprite();

    void centerSprite() const;

    void handleEvents();
    void updateViewportsOnResize(const sf::Event::Resized& event) const;

    static void updateMainView(const sf::Event::Resized& event);
    void updateTopView() const;
    void updateLeftView(const sf::Event::Resized& event) const;
    void updateRightView(const sf::Event::Resized& event) const;

};

