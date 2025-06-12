
#ifndef APP_H
#define APP_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

#include "Button.h"
#include "ColorScheme.h"

class App {

public:
    App(const std::string& title, sf::Vector2<float> windowDimensions, sf::Vector2<float> spriteScale, ColorScheme colorScheme);
    App();

    //Functions
    void update();

    sf::RenderWindow window;

private:

    //Window Properties
    std::string title;
    sf::Vector2<float> windowDimensions;

    //Image Texture Properties
    sf::Vector2<float> spriteScale;

    //Color
    sf::Color backgroundColor;

    std::unique_ptr<Button> button;


    std::unique_ptr<sf::View> view;
    sf::Texture imageTexture;
    //sf::Sprite *sprite{};
    std::unique_ptr<sf::Sprite> sprite;

    //Functions
    void centerSprite() const;

    void handleEvents();
    void setViewport(sf::Event::Resized event);

};

#endif //APP_H
