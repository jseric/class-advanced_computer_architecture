#pragma once

#include <cstdint>
#include <chrono>

class Timer
{
#pragma region Aliases
    using clock           = std::chrono::system_clock;
    using time_point_type = std::chrono::time_point<clock, std::chrono::milliseconds>;
#pragma endregion

private:
    time_point_type _start;

public:

    /*
     * Default constructor
     */
    Timer(void)
        : _start{ std::chrono::time_point_cast
                  <std::chrono::milliseconds>(clock::now()) }
    {
    }

    uint64_t GetTimePassed(void)
    {
        auto end = clock::now();

        return (end - _start).count();
    }
};
