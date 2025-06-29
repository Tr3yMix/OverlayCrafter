#pragma once

#include "Common.h"

#include <nfd.h>

inline void openTexture(sf::Texture &texture) {

    nfdchar_t* outPath = nullptr;

    const auto filterList = "png,jpg,jpeg,bmp";

    if(const nfdresult_t result = NFD_OpenDialog(filterList, nullptr, &outPath); result == NFD_OKAY) {
        sf::Image image;
        if(!image.loadFromFile(outPath)) {
            log(LogType::Error, "Failed to load image from: ", outPath);
            free(outPath);
            return;
        }

        if(auto size = image.getSize(); size.x != 16 || size.y != 16) {
            logf(LogType::Error, "Image size must be exactly 16x16 pixels. Got: {}x{}", size.x, size.y);
            free(outPath);
            return;
        }
        if(!texture.loadFromFile(outPath)) log(LogType::Error, "Failed to load texture from image.");
        else log(LogType::Info, "Successfully loaded minecraft texture from");

        free(outPath);
    }
    else if (result == NFD_ERROR) log(LogType::Error, "NFD error: ", NFD_GetError);

}

inline void openResourcePack() {
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
    }else if(result == NFD_ERROR) log(Logger::LogType::Error, "NFD error: ", NFD_GetError);
}

