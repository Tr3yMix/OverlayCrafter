#include "ProjectFile.h"

#include <fstream>

#include "FileDialog.h"
#include "Logger.h"
#include "SFML/Graphics/Image.hpp"


ProjectFile::ProjectFile() = default;

void ProjectFile::save(const sf::Texture &texture) {

    const auto filePathOpt = FileDialog::saveProjectFileDialog();

    if(!filePathOpt) return;

    const std::string& filePath = *filePathOpt;

    const sf::Image image = texture.copyToImage();

    const std::optional<std::vector<std::uint8_t>> dataOpt = image.saveToMemory("png");

    if(!dataOpt) {
        log(Logger::LogType::Error, "Failed to save image to memory.");
        return;
    }

    const std::vector<std::uint8_t>& pngData = *dataOpt;

    std::ofstream file(filePath, std::ios::binary);
    if(!file) {
        log(Logger::LogType::Error, "Failed to open file for writing.", filePath);
        return;
    }

    const auto size = static_cast<uint32_t>(pngData.size());
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    file.write(reinterpret_cast<const char*>(pngData.data()), size);

    log(Logger::LogType::Info, "Saved project file: ", filePath);
}

void ProjectFile::load(sf::Texture &texture) {

    const auto filePathOpt = FileDialog::openProjectFileDialog();

    if(!filePathOpt) return;

    const std::string& filePath = *filePathOpt;

    std::ifstream file(filePath, std::ios::binary);
    if(!file) {
        log(Logger::LogType::Error, "Failed to open file: ", filePath);
        return;
    }

    uint32_t size = 0;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));

    if(size == 0 || file.eof()) {
        log(Logger::LogType::Error, "Invalid or empty project file.");
        return;
    }

    std::vector<std::uint8_t> pngData(size);
    file.read(reinterpret_cast<char*>(pngData.data()), size);

    sf::Image image;

    if(!image.loadFromMemory(pngData.data(), size)) {
        log(Logger::LogType::Error, "Failed to load image from project file.");
        return;
    }

    if(!texture.loadFromImage(image)) {
        log(Logger::LogType::Error, "Failed to load texture from project image.");
        return;
    }

    log(Logger::LogType::Info, "Loaded project file: ", filePath);
}
