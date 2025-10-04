#pragma once

#include <string_view>
#include <unordered_map>
#include <memory>

#include "../general_constants.hpp"
#include "input_options/abs_get_img.hpp"

// --------loaders--------//
#include "input_options/path_upload.hpp"

class InputManager
{
public:
    InputManager();
    ~InputManager() = default;

    Status get_input();
    
private:
    static std::unordered_map<std::string_view, std::unique_ptr<AbsGetImg>> loader_names;
    std::string_view loader_name;

private:
    std::string_view choose_loader();
    
};
