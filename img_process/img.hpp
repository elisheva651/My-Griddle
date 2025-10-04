#pragma once

#include <vector>
#include <cstddef>
#include <algorithm>  
#include <cmath>
#include <cassert>

#include "img/constants.hpp"
#include "read_write/writer.hpp"
#include "img/pixels/pixel_abs.hpp"
#include "matrix.hpp"

namespace img
{

template <typename T = default_img_values_type> 
class Image
{

public:
    Image(const std::string& jpg_path, std::vector<std::pair<T, T>> ranges);
    ~Image() noexcept = default;

    PixelRgb<T>* operator[](size_t row) noexcept;

    const PixelRgb<T>* operator[](size_t row) const noexcept;
    
    // friend Writer<T>;
    std::pair<size_t, size_t> get_img_size() const;
    std::vector<std::pair<T, T>> get_ranges() const;

private:
    Matrix<PixelRgb<T>> pixels_; ///< Matrix storing the pixel data.
    std::vector<std::pair<T, T>> range_each_channel_; ///< Value range (min, max) for each channel.
    std::pair<size_t, size_t> img_size_; ///< Dimensions of the image (height, width).
};

} // namespace img

#include "img.inl"