#pragma once

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// Save image in the same directory as executable (not source file)
inline const std::string IMAGE_SAVE_FILENAME = "input.jpg";

// If you want it two directories up from current working directory:
inline const std::string IMAGE_SAVE_PATH = "";

// Combined path helper
inline std::string get_image_full_path() {
    return (fs::path(IMAGE_SAVE_PATH) / IMAGE_SAVE_FILENAME).string();
}

enum class GameType {
    GRIDDLE,
    NUM_GAMES
};

enum class Status {
    SUCCESS,
    IMG_LOAD_FAIL,
    FAIL,
    EXIT
};
