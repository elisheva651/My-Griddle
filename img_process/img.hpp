#pragma once

#include <vector>
#include <cstddef>
#include <utility>
#include <cassert>
#include "matrix.hpp"   // your Matrix class
#include "pixel.hpp"    // defines struct RGB

namespace img
{

class Image
{
public:
    explicit Image(const std::string& jpg_path);
    ~Image() noexcept = default;

    RGB* operator[](size_t row) noexcept;
    const RGB* operator[](size_t row) const noexcept;
    
    std::pair<size_t, size_t> get_img_size() const;

private:
    Matrix<RGB> m_pixels;                          ///< Matrix storing the pixel data.
    std::pair<size_t, size_t> m_img_size;          ///< Dimensions of the image (height, width).
};

} // namespace img
