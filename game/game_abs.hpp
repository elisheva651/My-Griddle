#pragma once

class AbsGame
{
private:
    /* data */
public:
    AbsGame() = default;
    virtual ~AbsGame() = default;

    virtual void run() = 0;
};
