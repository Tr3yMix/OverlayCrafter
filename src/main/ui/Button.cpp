
#include "Button.h"

#include <utility>


Button::Button(const ButtonType type, const sf::Vector2f& position, const sf::Vector2f& scale, const sf::Text& label, const Colors colors, const std::function<void()>& onClick): m_position(
                                                                                                                                                                                      position), m_scale(scale), m_colors(colors), m_type(type), m_clickCallback(onClick) {
    m_label = std::make_unique<sf::Text>(label);

    m_shape.setSize(m_scale);

    m_label->setPosition(m_position + m_scale / 2.f);
    m_shape.setPosition(m_position);

    m_shape.setFillColor(m_colors.button);
}

Button::Button(const ButtonType type, const sf::Vector2f& position, const sf::Vector2f& scale,
               sf::Font font, const std::string& text, const Colors &colors, const std::function<void()>& onClick)
    : m_position(position), m_scale(scale), m_font(std::move(font)), m_colors(colors), m_type(type),
      m_clickCallback(onClick) {
    m_label = std::make_unique<sf::Text>(m_font, text, sf::Text::Regular);

    m_label->setString(text);
    m_label->setScale({.35, .35});
    m_label->setFillColor(m_colors.text);
    const sf::FloatRect bounds = m_label->getLocalBounds();
    m_label->setOrigin({bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f + 5.f});

    m_shape.setSize(m_scale);


    m_label->setPosition(m_position + m_scale / 2.f);
    m_shape.setPosition(m_position);

    m_shape.setFillColor(m_colors.button);
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
    window.draw(*m_label);
}

bool Button::isHovering(const sf::RenderWindow& window, const sf::View& view) const {

    const sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

    return m_shape.getGlobalBounds().contains(mousePosition);

}




void Button::handleEvent(const std::optional<sf::Event>& event, const sf::RenderWindow& window, const sf::View& view) {

    if(isHovering(window, view)) {

        if(m_type == ButtonType::Critical) {
            m_shape.setFillColor(m_colors.critical);
        }else {
            m_shape.setFillColor(m_colors.highlight);
        }



        if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if(mouseButtonPressed->button == sf::Mouse::Button::Left) {
                if(m_clickCallback) {
                    m_clickCallback();
                }
            }
        }
    }
    else {
        m_shape.setFillColor(m_colors.button);

    }

}

void Button::setPosition(const sf::Vector2f& position) {
    m_shape.setPosition(position);
    m_label->setPosition(position + m_scale / 2.f);
}

void Button::setSize(const sf::Vector2f &scale) {
    m_scale = scale;
    m_shape.setSize(m_scale);

    const sf::FloatRect bounds = m_label->getLocalBounds();
    m_label->setOrigin({bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f});
}

sf::FloatRect Button::getBounds() const {
    return m_shape.getGlobalBounds();
}

sf::Vector2f Button::getScale() const {
    return m_scale;
}




