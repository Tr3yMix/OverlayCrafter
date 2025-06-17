
#ifndef NULLTEXTURE_H
#define NULLTEXTURE_H
#include <iostream>

#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Texture.hpp"


class WhiteTexture : public sf::Texture{

public:
    WhiteTexture() {
        if(const sf::Image image({1, 1}, sf::Color::White); !this->loadFromImage(image)) {
            std::cerr << "Failed to load null texture" << std::endl;
        }
    }

};



#endif //NULLTEXTURE_H
