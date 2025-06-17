
#include "image_loader.h"

#include <nfd.h>
#include <iostream>


void loadImage(sf::Texture &texture) {

    nfdchar_t* outPath = nullptr;

    const auto filterList = "png,jpg,jpeg,bmp";

    if(const nfdresult_t result = NFD_OpenDialog(filterList, nullptr, &outPath); result == NFD_OKAY) {
        if(!texture.loadFromFile(outPath)) {
            std::cerr << "Failed to load image from:"<< outPath << std::endl;
        }
        free(outPath);
    }
    else if (result == NFD_ERROR){
        std::cerr << "NFD error: "<< NFD_GetError << std::endl;
    }

}