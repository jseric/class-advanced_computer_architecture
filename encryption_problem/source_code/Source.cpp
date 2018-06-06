#include "EncryptionKeys.h"

#include <cstdint>
#include <iostream>

int main(void)
{
    // Sequential
    EncryptionKeys obj1;
    obj1.SetLimits(1, 10000000);

    uint64_t timePassed = obj1.Init();

    std::cout << "Passed time is " << timePassed << std::endl;
    std::cout << "################" << std::endl;

    std::cout << obj1.CounterToString();

    // Parallel 1
    EncryptionKeys obj2;
    obj2.SetLimits(1, 10000000);

    timePassed = obj2.InitThread();

    std::cout << "Passed time is " << timePassed << std::endl;
    std::cout << "################" << std::endl;

    std::cout << obj2.CounterToString();

    // Parallel 1
    EncryptionKeys obj3;
    obj3.SetLimits(1, 10000000);

    timePassed = obj3.InitThread(16);

    std::cout << "Passed time is " << timePassed << std::endl;
    std::cout << "################" << std::endl;

    std::cout << obj3.CounterToString();

    return 0;
}