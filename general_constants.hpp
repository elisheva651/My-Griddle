#pragma once

#include <string>

// Save image in the same directory as executable (not source file)
const std::string IMAGE_SAVE_FILENAME = "input.jpg";

// If you want it two directories up from current working directory:
const std::string IMAGE_SAVE_PATH = "";


enum class GameType {
    GRIDDLE,
    NUM_GAMES
};

typedef enum Status {
    SUCCESS,
    ING_LOAD_FAIL, 
    EXIT
} Status;