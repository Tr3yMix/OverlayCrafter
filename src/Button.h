
#ifndef BUTTON_H
#define BUTTON_H
#include <functional>

#include <SFML/Graphics.hpp>
#include "SFML/System/Vector2.hpp"

class Button {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& scale, const sf::Font& font,
        const std::string& text, sf::Color color, std::function<void()> onClick);

    void draw(sf::RenderWindow& window) const;
    void handleEvent(const std::optional<sf::Event>& event, const sf::RenderWindow& window);
    void setPosition(const sf::Vector2f& position);

private:

    sf::RectangleShape shape;
    std::unique_ptr<sf::Text> label;
    sf::Vector2f position;
    sf::Vector2f scale;
    sf::Font font;
    sf::Color color;

    std::function<void()> clickCallback;

    bool isHovering(const sf::RenderWindow& window) const;

};



#endif //BUTTON_H
