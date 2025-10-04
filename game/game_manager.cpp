#include "game_manager.hpp"
#include "griddle/griddle.hpp"
#include "../input/input_manager.hpp"
#include "img_process/img.hpp"

static std::unordered_map<GameType, std::unique_ptr<AbsGame>> init_map_game() {
    std::unordered_map<GameType, std::unique_ptr<AbsGame>> m;
    m.emplace(GameType::GRIDDLE, std::make_unique<Griddle>()); 
    return m;
}

std::unordered_map<GameType, std::unique_ptr<AbsGame>> GameManager::m_games = init_map_game();

GameManager::GameManager()
: m_game_type(choose_game())
{
}

void GameManager::run()
{
    //input
    if (input() != Status::SUCCESS) {
        return;
    }

    if (init() != Status::SUCCESS) {
        return;
    }
        // Image(const std::string& jpg_path, std::vector<std::pair<T, T>> ranges);

    

    
    //init
    //run
    //end
}


GameType GameManager::choose_game()
{
    // TODO - get from user which game to play.
    return GameType::GRIDDLE;
}

Status GameManager::input()
{
    switch (m_game_type) {
        case GameType::GRIDDLE: {
            InputManager input_manager{};
            if (input_manager.get_input() == Status::SUCCESS) {
                m_games[GameType::GRIDDLE]->run();
            }
            break;
        }
        default:
            break;
    }
    return Status::SUCCESS;
}

Status GameManager::init()
{
    try {
        std::string path = get_image_full_path();
        img::Image image(path);
    } catch (const std::exception& e) {
        return Status::FAIL;
    }
    return Status::SUCCESS;
}