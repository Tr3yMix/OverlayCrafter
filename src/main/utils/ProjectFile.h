#pragma once
#include "SFML/Graphics/Texture.hpp"


class ProjectFile {

public:

    ProjectFile();

    static void save(const sf::Texture& texture);

    static void load(sf::Texture &texture);

};

