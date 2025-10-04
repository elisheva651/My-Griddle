#pragma once

#include <map>
#include <vector>
#include "../matrix.hpp"
#include "../pixel.hpp"
#include "../img.hpp"

namespace img
{

using Type = unsigned char; // or whatever your pixel channel type is

class ColorReductionData;

class ColorReduction
{
public:
    explicit ColorReduction(int reduce_factor);

    Image process(Image const &source);

private:
    int reduce_factor_;
    std::vector<std::map<Type, Type>> fill_reduction_map(int reduce_factor);
};

class ColorReductionData
{
public:
    ColorReductionData(Image const &source,
                       int reduce_factor,
                       std::vector<std::map<Type, Type>> reduction_map);

    size_t height_;
    size_t width_;
    int reduce_factor_;
    std::vector<std::map<Type, Type>> reduction_map_;
};

} // namespace img
