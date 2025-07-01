#pragma once

#include <nfd.h>

#include "SFML/Graphics/Texture.hpp"

class FileDialog {
public:
    FileDialog();

    static void openTexture(sf::Texture& texture);
    static void generateMaskFromTexture(sf::Texture& texture);
    static void openResourcePack();



    static std::optional<std::string> openProjectFileDialog();
    static std::optional<std::string> saveProjectFileDialog();

private:
    static std::optional<std::string> openDialog(const nfdchar_t* filterList);
    static std::optional<std::string> saveDialog(const nfdchar_t* filterList, const std::string& endsWith = "");

};






