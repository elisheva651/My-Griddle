#include "griddle.hpp"
#include "../../img_process/processors/pixelate.hpp"
#include "../../img_process/processors/color_reduction.hpp"

#define BLOCK_SIZE 10

void Griddle::run()
{
}

Status Griddle::init()
{
    try {
        std::string path = get_image_full_path();
        m_img = img::Image(path); // assign a new Image object

        img::Pixelate pixelate(BLOCK_SIZE);
        img::ColorReduction color_reduction(2); // TODO - depend on user choose

        pixelate.process(m_img);
        img::Image final = color_reduction.process(pixelate.process(m_img));

        std::string img_game_path = get_game_image_full_path();
        final.save_to_file(img_game_path);

    } catch (const std::exception& e) {
        return Status::FAIL;
    }
    return Status::SUCCESS;
}
