#include <SFML/Graphics.hpp>

#include "image_loader.h"
#include "App.h"
#include "Button.h"
#include "ResourceManager.h"
#include "WhiteTexture.h"

App::App(const std::string& title, const sf::Vector2<float> windowDimensions, const sf::Vector2<float> spriteScale,
         const ColorScheme colorScheme) : title(title), windowDimensions(windowDimensions), spriteScale(spriteScale),
        backgroundColor(colorScheme.backgroundColor), imageTexture(WhiteTexture()){

    window.create(sf::VideoMode(static_cast<sf::Vector2u>(windowDimensions)), title,
                  sf::Style::Default, sf::State::Windowed);

    view = std::make_unique<sf::View>(sf::FloatRect({0, 0}, windowDimensions));

    if(!font.openFromFile(ResourceManager::resourcePath / "font" / "arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }

    sf::Vector2f position = {20, 50};
    sf::Vector2f scale = {300, 50};

    button = std::make_unique<Button>(position, scale, font, "Open File", colorScheme.buttonColor,[this] {
        loadImage(imageTexture);
        sprite->setTexture(imageTexture, true);
        centerSprite();
    });

    sprite = std::make_unique<sf::Sprite>(imageTexture);

    sprite->setScale(this->spriteScale);

    centerSprite();


}

App::App(): App("app", sf::Vector2f(800, 600), sf::Vector2f(16, 16), ColorScheme::Light()){

}

void App::setViewport(const sf::Event::Resized& event) {
    const float windowAspect = static_cast<float>(event.size.x) / static_cast<float>(event.size.y);
    const float viewAspect = view->getSize().x / view->getSize().y;

    float sizeX = 1.f;
    float sizeY = 1.f;
    float posX = 0.f;
    float posY = 0.f;

    if(windowAspect > viewAspect) {
        sizeX = viewAspect / windowAspect;
        posX = (1.f - sizeX) / 2.f;
    }else {
        sizeY = windowAspect / viewAspect;
        posY = (1.f - sizeY) / 2.f;
    }

    view->setViewport(sf::FloatRect({posX, posY}, {sizeX, sizeY}));
    window.setView(*view);
}

void App::updateButtonPosition() const {
    constexpr float marginLeft = 20.f;
    constexpr float marginTop = 50.f;
    button->setPosition({marginLeft, marginTop});
}


void App::update() {

    handleEvents();

    window.setView(*view);

    window.clear(backgroundColor);

    button->draw(window);

    window.draw(*sprite);

    window.display();
}

void App::centerSprite() const {
    const sf::Vector2u windowSize = window.getSize();
    const sf::FloatRect spriteBounds = sprite->getGlobalBounds();

    const float posX = (static_cast<float>(windowSize.x) - spriteBounds.size.x) / 2.f;
    const float posY = (static_cast<float>(windowSize.y) - spriteBounds.size.y) / 2.f;

    sprite->setPosition(sf::Vector2f(posX, posY));
}

void App::handleEvents() {

    while(const std::optional<sf::Event> event = window.pollEvent()) {

        if(event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if(const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if(key->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
            }
        }else if(const auto* resized = event->getIf<sf::Event::Resized>()) {
            setViewport(*resized);
            updateButtonPosition();
        }

        button->handleEvent(event, window);
    }
}





