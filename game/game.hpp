#pragma once

#include <string_view>
#include <unordered_map>
#include <memory>

#include "game_abs.hpp"
#include "griddle/griddle.hpp"

class Game
{

public:
    Game(std::string_view game_name);
    ~Game() = default;
    
private:
    static std::unordered_map<std::string_view, std::unique_ptr<AbsGame>> games;
};
