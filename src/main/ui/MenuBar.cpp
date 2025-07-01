#include "MenuBar.h"

#include <utility>

#include "utils/Theme.h"


MenuBar::MenuBar(const MenuType type, const sf::Vector2u& size, const Colors colors, sf::Font font):
m_type(type), m_size(size), m_colors(colors), m_font(std::move(font)) {

    m_background.setSize(sf::Vector2f(m_size));
    m_background.setFillColor(m_colors.foreground);
    m_background.setPosition({0, 0});

}

void MenuBar::addButton(const std::string &text, const std::function<void()>& onClick) {

    sf::Vector2f position;

    if(m_type != MenuType::Horizontal) {
        const float y = m_padding + static_cast<float>(m_buttons.size()) * (m_buttonHeight + m_padding);

        position.x = m_padding;
        position.y = y;

        sf::Vector2f scale(m_buttonWidth, m_buttonHeight);

        m_buttons.emplace_back(std::make_unique<Button>(ButtonType::Normal, position, scale, m_font, text, m_colors, onClick));
    }
    else {
        sf::Text label(m_font, text, sf::Text::Regular);


        label.setScale({.35f, .35f});
        label.setFillColor(m_colors.text);
        const sf::FloatRect bounds = label.getLocalBounds();
        label.setOrigin({bounds.position.x + bounds.size.x /2.f, bounds.position.y + bounds.size.y / 2.f});


        const float buttonWidth = bounds.size.x / 2.5f;

        sf::Vector2f scale(buttonWidth, m_buttonHeight);

        float x = m_padding;

        for(const auto& button : m_buttons) {
            x += button->getScale().x + m_padding;
        }

        position.x = x;
        position.y = 0;

        m_buttons.emplace_back(std::make_unique<Button>(ButtonType::Normal, position, scale, label, m_colors, onClick));
    }


}

void MenuBar::draw(sf::RenderWindow& window, const sf::View& topView, const sf::View& leftView) const {

    window.setView(topView);

    window.draw(m_background);

    window.setView(leftView);
    for(const auto& button : m_buttons) button->draw(window);

}

void MenuBar::handleButtonEvents(const std::optional<sf::Event> &event, const sf::RenderWindow &window, const sf::View& view) {
    for(const auto& button : m_buttons) button->handleEvent(event, window, view);
}




