#pragma once

#include "../game_abs.hpp"

class Griddle : public AbsGame
{
private:
    /* data */
public:
    Griddle(/* args */);
    ~Griddle();

    void run() override;
};
