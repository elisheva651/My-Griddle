#pragma once

#include "../../status.hpp"

// notice ! all loaders have to save the image in the same path and name.
// see in general_constants.hpp

class AbsGetImg
{
 
public:
    AbsGetImg() = default;
    virtual ~AbsGetImg() = default;

    virtual Status receive_input() = 0;
};
