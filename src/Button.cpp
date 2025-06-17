
#include "Button.h"


Button::Button(const sf::Vector2f& position, const sf::Vector2f& scale,
               const sf::Font& font, const std::string& text, const sf::Color color, const std::function<void()> onClick)
: clickCallback(onClick) {

    this->position = position;
    this->scale = scale;
    this->font = font;
    this->color = color;

    shape.setPosition(this->position);
    shape.setSize(this->scale);
    shape.setFillColor(this->color);

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

bool Button::isHovering(const sf::RenderWindow& window) const {

    const sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    return shape.getGlobalBounds().contains(mousePosition);

}


void Button::handleEvent(const std::optional<sf::Event>& event, const sf::RenderWindow& window){

    if(isHovering(window)) {

        shape.setFillColor(sf::Color::Green);

        if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if(mouseButtonPressed->button == sf::Mouse::Button::Left) {
                if(clickCallback) {
                    clickCallback();
                }
            }
        }
    }
    else {
        shape.setFillColor(this->color);

    }

}


