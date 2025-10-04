#pragma once

#include "../pixelate.hpp"

namespace img
{

Pixelate::Pixelate(size_t square_wall_len)
: square_wall_len_(square_wall_len)
{
}


Image Pixelate::process(Image const &source)
{
    PixelateData data(source, square_wall_len_);
    Matrix<PixelRgb> pixels(data.height_, data.width_);

    for (size_t block_row = 0; block_row < data.height_; block_row += data.square_wall_len_) {
        for (size_t block_col = 0; block_col < data.width_; block_col += data.square_wall_len_) {
            avg_each_channel(source, data, pixels, block_row, block_col);
        }
    }

    return Image(pixels);  
}

PixelateData::PixelateData(Image const &source, size_t square_wall_len)
: height_(source.get_img_size().first)
, width_(source.get_img_size().second)
, square_wall_len_(square_wall_len)
, num_channels_(source.get_ranges().size())
{
}

void avg_each_channel(Image const &source, PixelateData const& data, Matrix<PixelRgb>& pixels, size_t block_row, size_t block_col) {
    size_t real_block_height = std::min(data.square_wall_len_, data.height_ - block_row);
    size_t real_block_width  = std::min(data.square_wall_len_, data.width_ - block_col);

    size_t count = real_block_height * real_block_width;
    uint32_t sum_r = 0, sum_g = 0, sum_b = 0;

    // Sum all pixel channels in the block
    for (size_t i = 0; i < real_block_height; ++i) {
        for (size_t j = 0; j < real_block_width; ++j) {
            size_t row = block_row + i;
            size_t col = block_col + j;

            const PixelRgb &p = source[row][col];
            sum_r += p.r;
            sum_g += p.g;
            sum_b += p.b;
        }
    }

    // Average
    uint8_t avg_r = static_cast<uint8_t>(sum_r / count);
    uint8_t avg_g = static_cast<uint8_t>(sum_g / count);
    uint8_t avg_b = static_cast<uint8_t>(sum_b / count);

    // Fill the block in the output matrix
    for (size_t i = 0; i < real_block_height; ++i) {
        for (size_t j = 0; j < real_block_width; ++j) {
            size_t row = block_row + i;
            size_t col = block_col + j;

            pixels[row][col] = PixelRgb{avg_r, avg_g, avg_b};
        }
    }
}

    
} // namespace img