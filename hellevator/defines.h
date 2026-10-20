#pragma once

#include <QString>

enum class Direction 
{ 
    STOP = 0, 
    UP = 1, 
    DOWN = -1 
};

constexpr int NO_TARGET = -1;

inline QString directionToString(Direction dir) 
{
    switch(dir) 
    {
        case Direction::UP: 
            return "UP";
        case Direction::DOWN: 
            return "DOWN";
        default: 
            return "STOP";
    }
}