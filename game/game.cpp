
#include "game.hpp"
#include "game_abs.hpp"

static std::unordered_map<std::string_view, std::unique_ptr<AbsGame>> make_games() {
    std::unordered_map<std::string_view, std::unique_ptr<AbsGame>> m;
    m.emplace("griddle", std::make_unique<Griddle>());
    return m;
}

std::unordered_map<std::string_view, std::unique_ptr<AbsGame>> Game::games = make_games();

Game::Game(std::string_view game_name)
{
    auto& game_ptr = games.at(game_name); // get reference to the unique_ptr
    game_ptr->run();
}


