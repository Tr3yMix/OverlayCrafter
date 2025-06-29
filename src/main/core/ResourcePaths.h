#pragma once

#include <filesystem>

namespace ResourcePaths {
    static const std::filesystem::path resourcePath(RESOURCE_DIR);

    static const std::filesystem::path fontPath(resourcePath / "font/");

    static const std::filesystem::path imagePath(resourcePath / "image/");
}

