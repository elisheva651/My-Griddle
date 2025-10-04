#include "input_manager.hpp"
#include "input_options/path_upload.hpp"

static std::unordered_map<std::string_view, std::unique_ptr<AbsGetImg>> init_loaders() {
    std::unordered_map<std::string_view, std::unique_ptr<AbsGetImg>> m;
    m.emplace("upload", std::make_unique<PathUpload>());
    return m;
}

std::unordered_map<std::string_view, std::unique_ptr<AbsGetImg>> InputManager::loader_names = init_loaders();

InputManager::InputManager()
: loader_name(choose_loader())
{
}

std::string_view InputManager::choose_loader()
{
    // TODO - get from user which loader to use.
    return "upload";
}

Status InputManager::get_input()
{
    Status status = loader_names[loader_name]->receive_input();
    while (status != SUCCESS && status != EXIT)
    {
        status = loader_names[loader_name]->receive_input();
    }
    
    return SUCCESS;
}
