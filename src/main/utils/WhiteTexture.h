#pragma once

#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Texture.hpp"

class WhiteTexture : public sf::Texture{

public:
    WhiteTexture() {
        if(const sf::Image image({16, 16}, sf::Color::White); !this->loadFromImage(image)) {
            Logger::log(Logger::LogType::Error, "Failed to load white texture");
        }
    }

};
