#pragma once

#include "abs_processor.hpp"
#include "../matrix.hpp"
#include "../pixel.hpp"

namespace img
{

struct PixelateData;

class Pixelate : public AbsProcessors
{

public:
    Pixelate() = delete;
    explicit Pixelate(size_t square_wall_len);
    ~Pixelate() noexcept override = default;

    Image process(Image const& source) override;

private:
    size_t square_wall_len_;

private:
    void avg_each_channel(Image const &source, PixelateData const& data, Matrix<RGB>& pixels, size_t block_row, size_t block_col);
};

struct PixelateData
{
    PixelateData(Image const& source, size_t square_wall_len);
    ~PixelateData() noexcept = default;

    size_t height_;
    size_t width_;
    size_t square_wall_len_;
};

} // namespace img
