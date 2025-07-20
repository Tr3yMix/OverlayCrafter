#pragma once

#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Texture.hpp"

inline sf::Texture whiteTexture() {
    const sf::Image img({16, 16}, sf::Color::White);

    sf::Texture texture;
    if(!texture.loadFromImage(img)) {
        log(Logger::LogType::Error, "Failed to load white texture");
    }

    return texture;

}

