#include <map>
#include <vector>
#include <cmath>
#include <algorithm>

#include "color_reduction.hpp"
#include "../img.hpp"
#include "../pixel.hpp"
#include "../matrix.hpp"
#include "pixelate.hpp"

namespace img
{

std::vector<std::map<Type, Type>> fill_reduction_map(int reduce_factor) {
    std::vector<std::map<Type, Type>> reduction_maps(3); 
 
    for (size_t channel_ind = 0; channel_ind < 3; ++channel_ind) {
        for (Type value = 0; value <= 255; ++value) {  // map 0-255
            Type step = (reduce_factor > 1) ? 255 / (reduce_factor - 1) : 1;
            Type reduced_value = std::round(static_cast<double>(value) / step) * step;
            reduced_value = std::clamp(reduced_value, Type(0), Type(255));
            reduction_maps[channel_ind][value] = reduced_value;
        }
    }

    return reduction_maps;
}

ColorReduction::ColorReduction(int reduce_factor)
: reduce_factor_(reduce_factor)
{
}


ColorReductionData::ColorReductionData(Image const &source, int reduce_factor)
: height_(source.get_img_size().first)
, width_(source.get_img_size().second)
, reduce_factor_(reduce_factor)
, reduction_map_(fill_reduction_map(reduce_factor_))
{
}

void img::Pixelate::avg_each_channel(Image const &source, PixelateData const& data, Matrix<RGB>& pixels, size_t block_row, size_t block_col) {
    size_t real_block_height = std::min(data.square_wall_len_, data.height_ - block_row);
    size_t real_block_width  = std::min(data.square_wall_len_, data.width_ - block_col);

    size_t count = 0;
    std::vector<uint8_t> avg_in_channel(3, 0); // assuming 3 channels

    for (size_t i = 0; i < real_block_height; ++i) {
        for (size_t j = 0; j < real_block_width; ++j) {
            size_t row = block_row + i;
            size_t col = block_col + j;

            avg_in_channel[0] += source[row][col].r;
            avg_in_channel[1] += source[row][col].g;
            avg_in_channel[2] += source[row][col].b;

            ++count;
        }
    }

    for (int channel = 0; channel < 3; ++channel) {
        avg_in_channel[channel] /= count;
    }

    for (size_t i = 0; i < real_block_height; ++i) {
        for (size_t j = 0; j < real_block_width; ++j) {
            size_t row = block_row + i;
            size_t col = block_col + j;

            pixels[row][col].r = avg_in_channel[0];
            pixels[row][col].g = avg_in_channel[1];
            pixels[row][col].b = avg_in_channel[2];
        }
    }
}


Image ColorReduction::process(Image const &source)
{
    ColorReductionData data(source, reduce_factor_ );
    Matrix<RGB> pixels(data.height_, data.width_);

    for (size_t row = 0; row < data.height_; ++row) {
        for (size_t col = 0; col < data.width_; ++col) {
            pixels[row][col].r = data.reduction_map_[0][source[row][col].r];
            pixels[row][col].g = data.reduction_map_[1][source[row][col].g];
            pixels[row][col].b = data.reduction_map_[2][source[row][col].b];
        }
    }

    return Image(pixels);
}

} // namespace img