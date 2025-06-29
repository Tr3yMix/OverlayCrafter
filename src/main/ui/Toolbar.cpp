#include "Toolbar.h"

#include <utility>

#include "utils/Theme.h"


Toolbar::Toolbar(const sf::Vector2u& size, const Colors colors ,sf::Font font): m_font(std::move(font)), m_colors(colors){
    m_background.setSize(sf::Vector2f(size));
    m_background.setFillColor(m_colors.foreground);
    m_background.setPosition({0, 0});
}

void Toolbar::addButton(const std::string &label, const std::function<void()>& onClick) {

    const float x = m_padding + static_cast<float>(m_buttons.size()) * (m_buttonWidth + m_padding);

    sf::Vector2f position(x, m_padding);
    sf::Vector2f scale(m_buttonWidth, m_buttonHeight);

    m_buttons.emplace_back(std::make_unique<Button>(position, scale, m_font, label, m_colors, onClick));
}

void Toolbar::draw(sf::RenderWindow &window) const {

    window.draw(m_background);

    for(const auto& button : m_buttons) button->draw(window);

}

void Toolbar::handleEvent(const std::optional<sf::Event> &event, const sf::RenderWindow &window) {
    for(const auto& button : m_buttons) button->handleEvent(event, window);
}

void Toolbar::resize(const sf::Vector2u &size) {
    m_background.setSize(sf::Vector2f(size));
}


