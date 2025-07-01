#pragma once

#include "Button.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "utils/Theme.h"

enum class MenuType {Horizontal, Vertical, DropDown};

class MenuBar {

public:
    MenuBar(MenuType type,const sf::Vector2u& size, Colors colors ,sf::Font font);

    void addButton(const std::string& text, const std::function<void()>& onClick);
    void draw(sf::RenderWindow& window, const sf::View& topView, const sf::View& leftView) const;
    void handleButtonEvents(const std::optional<sf::Event>& event, const sf::RenderWindow& window, const sf::View& view);
    //void resize(const sf::Vector2u& size);

private:

    MenuType m_type;
    sf::Vector2u m_size;
    Colors m_colors;
    sf::RectangleShape m_background;
    std::vector<std::unique_ptr<Button>> m_buttons;
    sf::Font m_font;

    float m_buttonWidth = 50.f;
    float m_buttonHeight = 35.f;
    float m_padding = 1.f;
};
