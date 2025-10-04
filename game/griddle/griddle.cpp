#include "griddle.hpp"


Griddle::Griddle()
{
}

Griddle::~Griddle()
{
}

void Griddle::run()
{
}

Status Griddle::init()
{
    try {
        std::string path = get_image_full_path();
        m_image(path);
    } catch (const std::exception& e) {
        return Status::FAIL;
    }
    return Status::SUCCESS;
}
