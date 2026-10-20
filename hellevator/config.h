#pragma once

namespace Config 
{
    constexpr int FIRST_FLOOR = 1;
    constexpr int LAST_FLOOR = 9;
    constexpr int FLOORS_COUNT = (LAST_FLOOR - FIRST_FLOOR + 1);

    constexpr int DOOR_TIME = 2000;
    constexpr int WAIT_TIME = 3000;
    constexpr int FLOOR_PASS_TIME = 1500;
}