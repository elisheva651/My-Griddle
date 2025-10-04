#pragma once

#include "img/img.hpp"

namespace img
{

template <typename T>
class AbsProcessors
{
public:
    AbsProcessors() = default;

    virtual ~AbsProcessors() noexcept = default;

    virtual Image<T> process(Image<T> const& source) = 0;
};

} // namespace img