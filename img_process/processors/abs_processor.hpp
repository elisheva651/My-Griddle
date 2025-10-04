#pragma once

#include "../img.hpp"

namespace img
{

class AbsProcessors
{
public:
    AbsProcessors() = default;

    virtual ~AbsProcessors() noexcept = default;

    virtual Image process(Image const& source) = 0;
};

} // namespace img