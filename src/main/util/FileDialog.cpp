#include "FileDialog.h"

#include "SFML/Graphics/Image.hpp"

#include <nfd.h>
#include <ranges>

#include "Logger.h"

using namespace Logger;

FileDialog::FileDialog() = default;


std::optional<std::string> FileDialog::saveDialog(const nfdchar_t* filterList, const std::string& endsWith) {
    nfdchar_t* outPath = nullptr;

    if(const nfdresult_t result = NFD_SaveDialog(filterList, nullptr, &outPath); result == NFD_OKAY) {
        std::string resultStr(outPath);
        free(outPath);

        if(!endsWith.empty()) {
            if(!resultStr.ends_with(endsWith)) {
                resultStr += endsWith;
            }
        }

        return resultStr;
    }else if(result == NFD_ERROR) {
        log(LogType::Error, "NFD error: ", NFD_GetError());
    }

    return std::nullopt;
}


std::optional<std::string> FileDialog::openDialog(const nfdchar_t* filterList) {
    nfdchar_t* outPath = nullptr;

    if(const nfdresult_t result = NFD_OpenDialog(filterList, nullptr, &outPath); result == NFD_OKAY) {
        std::string resultStr(outPath);
        free(outPath);
        return resultStr;
    }else if(result == NFD_ERROR) {
        log(LogType::Error, "NFD error: ", NFD_GetError());
    }
    return std::nullopt;
}




std::optional<std::string> FileDialog::saveProjectFileDialog() {return saveDialog("oc", ".oc");}

std::optional<std::string> FileDialog::openProjectFileDialog() {return openDialog("oc");}


void FileDialog::openTexture(sf::Texture& texture) {

    nfdchar_t* outPath = nullptr;

    const auto filterList = "png,jpg,jpeg,bmp";

    if(const nfdresult_t result = NFD_OpenDialog(filterList, nullptr, &outPath); result == NFD_OKAY) {
        [[maybe_unused]] std::unique_ptr<nfdchar_t, decltype(&free)> outPathGuard(outPath, free);
        sf::Image image;
        if(!image.loadFromFile(outPath)) {
            log(LogType::Error, "Failed to load image from: ", outPath);
            return;
        }
        if(auto size = image.getSize(); size.x != 16 || size.y != 16) {
            logf(LogType::Error, "Image size must be exactly 16x16 pixels. Got: {}x{}", size.x, size.y);
            return;
        }
        if(!texture.loadFromFile(outPath)) log(LogType::Error, "Failed to load texture from image.");
        else log(LogType::Info, "Successfully loaded minecraft texture from: ", outPath);
    }
    else if (result == NFD_ERROR) log(LogType::Error, "NFD error: ", NFD_GetError);

}

void FileDialog::generateMaskFromTexture(sf::Texture& texture) {

    sf::Texture maskTexture;

    openTexture(maskTexture);

    const sf::Image maskImage = maskTexture.copyToImage();
    sf::Image finalImage = texture.copyToImage();

    const sf::Vector2u size = maskImage.getSize();
    for(unsigned int x = 0; x < size.x; x++) {
        for(unsigned int y = 0; y < size.y; y++) {
            if(maskImage.getPixel(sf::Vector2u(x, y)).a == 0){
                finalImage.setPixel(sf::Vector2u(x, y), sf::Color::Transparent);
            }
        }
    }
    if(!texture.loadFromImage(finalImage)) log(LogType::Error, "Failed to load texture from mask.");
    else log(LogType::Info, "Successfully generated mask");

}

void FileDialog::openResourcePack() {
    nfdchar_t* outPath = nullptr;

    if(const nfdresult_t result = NFD_PickFolder(nullptr, &outPath); result == NFD_OKAY) {
        const std::filesystem::path packPath(outPath);
        free(outPath);

        const std::string packName = packPath.filename().string();

        const std::filesystem::path ctmPath = packPath / "assets/minecraft/optifine/ctm";

        if(!exists(ctmPath) || !is_directory(ctmPath)) {
            logf(LogType::Error, "CTM path not found in '{}'", packName);
            return;
        }

        size_t categoryCount = 0;
        size_t overlayCount = 0;

        for(const auto &entry : std::filesystem::directory_iterator(ctmPath)) {
            if(entry.is_directory()) {
                if(const std::string name = entry.path().filename().string(); name != "_overlays") categoryCount++;
            }
        }

        if(const std::filesystem::path overlaysPath = ctmPath / "_overlays"; exists(overlaysPath) && is_directory(overlaysPath)) {
            for(const auto &entry : std::filesystem::directory_iterator(overlaysPath)) if(entry.is_directory()) overlayCount++;
        }

        logf(LogType::Info, "Resource pack '{}' found with {} categories and {} overlays ", packName, categoryCount, overlayCount);
    }else if(result == NFD_ERROR) log(LogType::Error, "NFD error: ", NFD_GetError);
}



