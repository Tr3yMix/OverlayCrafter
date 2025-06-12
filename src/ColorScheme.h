
#ifndef COLORSCHEME_H
#define COLORSCHEME_H
#include "SFML/Graphics.hpp"


class ColorScheme {

public:
    ColorScheme(sf::Color backgroundColor, sf::Color foregroundColor, sf::Color buttonColor);
    ColorScheme();

    sf::Color backgroundColor;
    sf::Color foregroundColor;
    sf::Color buttonColor;
};



#endif //COLORSCHEME_H
