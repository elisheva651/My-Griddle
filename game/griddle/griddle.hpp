#pragma once

#include "../game_abs.hpp"
#include "../../general_constants.hpp"
#include "../../img_process/img.hpp"

class Griddle : public AbsGame
{

public:
    Griddle() = default;
    ~Griddle() noexcept = default;

    void run() override;
    Status init() override;
    
private:
    img::Image m_img;
};
