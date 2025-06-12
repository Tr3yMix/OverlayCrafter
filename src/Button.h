
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
    void handleEvent(const std::optional<sf::Event>& event, const sf::RenderWindow& window) const;

private:

    sf::RectangleShape shape;
    std::unique_ptr<sf::Text> label;
    sf::Vector2f position;
    sf::Vector2f scale;
    sf::Font font;

    std::function<void()> clickCallback;

};



#endif //BUTTON_H
