#pragma once

#include <map>

#include "abs_processor.hpp"

namespace img
{

using Type = uint16_t;

class ColorReduction : public AbsProcessors
{
public:
    explicit ColorReduction(int reduce_factor = 0);
    ~ColorReduction() noexcept override = default;

    Image process(Image const &source) override;
private:
    int reduce_factor_;

private:
    std::vector<std::map<Type, Type>> fill_reduction_map(int reduce_factor);

};

struct ColorReductionData
{
    ColorReductionData(Image const& source, int reduce_factor);
    ~ColorReductionData() noexcept = default;

    size_t height_;
    size_t width_;
    int reduce_factor_;
    std::vector<std::map<Type, Type>> reduction_map_;
};

} // namespace img
