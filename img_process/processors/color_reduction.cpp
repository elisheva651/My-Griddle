#include <map>
#include <vector>
#include <cmath>
#include <algorithm>

#include "color_reduction.hpp"
#include "../img.hpp"
#include "../pixel.hpp"
#include "../matrix.hpp"

namespace img
{

ColorReduction::ColorReduction(int reduce_factor)
    : reduce_factor_(reduce_factor)
{
}

ColorReductionData::ColorReductionData(Image const &source, int reduce_factor, std::vector<std::map<Type, Type>> reduction_map)
: height_(source.get_img_size().first)
, width_(source.get_img_size().second)
, reduce_factor_(reduce_factor)
, reduction_map_(std::move(reduction_map))
{
}

Image ColorReduction::process(Image const &source)
{
    Matrix<RGB> pixels(source.get_img_size().first, source.get_img_size().second);

    int levels = std::max(2, reduce_factor_); // at least 2 levels
    int step = 255 / (levels - 1);

    for (size_t row = 0; row < source.get_img_size().first; ++row)
    {
        for (size_t col = 0; col < source.get_img_size().second; ++col)
        {
            RGB orig = source[row][col];

            // convert to grayscale intensity
            int gray = static_cast<int>(0.3 * orig.r + 0.59 * orig.g + 0.11 * orig.b);

            // quantize into N bins
            int reduced = std::round(static_cast<double>(gray) / step) * step;
            reduced = std::clamp(reduced, 0, 255);

            // set pixel as grayscale
            pixels[row][col] = RGB{static_cast<uint8_t>(reduced),
                                   static_cast<uint8_t>(reduced),
                                   static_cast<uint8_t>(reduced)};
        }
    }

    return Image(pixels);
}



std::vector<std::map<Type, Type>> ColorReduction::fill_reduction_map(int reduce_factor)
{
    std::vector<std::map<Type, Type>> reduction_maps(3);

    for (size_t channel_ind = 0; channel_ind < 3; ++channel_ind)
    {
        for (int value = 0; value <= 255; ++value)
        {
            Type step = (reduce_factor > 1) ? 255 / (reduce_factor - 1) : 1;
            Type reduced_value = std::round(static_cast<double>(value) / step) * step;
            reduced_value = std::clamp(reduced_value, Type(0), Type(255));
            reduction_maps[channel_ind][value] = reduced_value;
        }
    }

    return reduction_maps;
}
 
} // namespace img
