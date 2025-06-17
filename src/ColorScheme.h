
#ifndef COLORSCHEME_H
#define COLORSCHEME_H
#include "SFML/Graphics.hpp"


class ColorScheme {

public:
    ColorScheme(sf::Color backgroundColor, sf::Color foregroundColor, sf::Color buttonColor, sf::Color textColor);

    static ColorScheme Dark();
    static ColorScheme Light();

    sf::Color backgroundColor;
    sf::Color foregroundColor;
    sf::Color buttonColor;
    sf::Color textColor;
};



#endif //COLORSCHEME_H
