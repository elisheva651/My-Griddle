#pragma once

#include "../general_constants.hpp"

class AbsGame
{
private:
    /* data */
public:
    AbsGame() = default;
    virtual ~AbsGame() = default;

    virtual void run() = 0;
    virtual Status init() = 0;
};
