#pragma once

#include "Button.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "utils/Theme.h"

class Toolbar {

public:
    Toolbar(const sf::Vector2u& size, Colors colors ,sf::Font font);

    void addButton(const std::string& label, const std::function<void()>& onClick);
    void draw(sf::RenderWindow& window) const;
    void handleEvent(const std::optional<sf::Event>& event, const sf::RenderWindow& window);
    void resize(const sf::Vector2u& size);

private:

    Colors m_colors;
    sf::RectangleShape m_background;
    std::vector<std::unique_ptr<Button>> m_buttons;
    sf::Font m_font;
    float m_buttonWidth = 100.f;
    float m_buttonHeight = 30.f;
    float m_padding = 10.f;
};
