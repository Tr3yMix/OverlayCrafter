
#include "image_loader.h"
#include "libs/tinyfiledialogs.h"

#include <iostream>


void loadImage(sf::Texture &texture) {
    const char* filters[] = { "*.png", "*.jpg", "*.jpeg", "*.bmp" };
    const char* filePath = tinyfd_openFileDialog(
        "Open Texture",
        "",
        4,
        filters,
        "Image Files",
        0
        );

    if(filePath) {
        if(!texture.loadFromFile(filePath)) {
            std::cerr << "Failed to load image from: " << filePath << std::endl;
        }
    }
    else {
        std::cerr << "File path failed to load" << std::endl;
    }
}