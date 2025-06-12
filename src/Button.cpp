
#include "Button.h"

#include <iostream>


Button::Button(const sf::Vector2f& position, const sf::Vector2f& scale,
               const sf::Font& font, const std::string& text, const sf::Color color, const std::function<void()> onClick)
: clickCallback(onClick) {

    this->position = position;
    this->scale = scale;
    this->font = font;

    shape.setPosition(this->position);
    shape.setSize(this->scale);
    shape.setFillColor(color);

    label = std::make_unique<sf::Text>(this->font, text);

    label->setString(text);
    label->setCharacterSize(18);
    label->setFillColor(sf::Color::White);
    const sf::FloatRect bounds = label->getLocalBounds();
    label->setOrigin({bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f});
    label->setPosition(this->position + this->scale / 2.f);
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(*label);
}

void Button::handleEvent(const std::optional<sf::Event>& event, const sf::RenderWindow& window) const {
    if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if(mouseButtonPressed->button == sf::Mouse::Button::Left) {
            const sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if(const sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)); shape.getGlobalBounds().contains(mousePosF)) {
                if(clickCallback) {
                    clickCallback();
                }
            }
        }
    }

}
