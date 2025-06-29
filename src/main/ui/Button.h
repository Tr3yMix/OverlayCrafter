#pragma once

#include <functional>

#include <SFML/Graphics.hpp>
#include "SFML/System/Vector2.hpp"
#include "utils/Theme.h"

class Button {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& scale, sf::Font  font,
        const std::string& text, Colors colors, const std::function<void()>& onClick);

    void draw(sf::RenderWindow& window) const;
    void handleEvent(const std::optional<sf::Event>& event, const sf::RenderWindow& window);
    void setPosition(const sf::Vector2f& position);

private:

    sf::RectangleShape m_shape;
    std::unique_ptr<sf::Text> m_label;
    sf::Vector2f m_position;
    sf::Vector2f m_scale;
    sf::Font m_font;
    Colors m_colors;

    std::function<void()> m_clickCallback;

    bool isHovering(const sf::RenderWindow& window) const;

};

