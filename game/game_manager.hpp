#pragma once

#include <unordered_map>
#include <memory>

#include "game_abs.hpp"

#include "../general_constants.hpp"

class GameManager
{
public:
    GameManager();
    ~GameManager() = default;

    void run();

private:
    static std::unordered_map<GameType, std::unique_ptr<AbsGame>> m_games;
    GameType m_game_type;

private:
    GameType choose_game();
    Status input();
    
};
