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
    Image() = default;
    explicit Image(const std::string& jpg_path);
    explicit Image(const Matrix<RGB>& pixels);

    ~Image() noexcept = default;

    RGB* operator[](size_t row) noexcept;
    const RGB* operator[](size_t row) const noexcept;
    
    std::pair<size_t, size_t> get_img_size() const;
    void save_to_file(const std::string& path) const;
private:
    Matrix<RGB> m_pixels;          
    std::pair<size_t, size_t> m_img_size;
    
};

} // namespace img
