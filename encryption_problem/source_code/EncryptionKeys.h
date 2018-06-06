#pragma once

#include "Timer.h"

#include <cmath>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

class EncryptionKeys
{
private:

#pragma region Private Members

    /*
     * Key min and max limit
     */
    uint64_t _lowerLimit;
    uint64_t _upperLimit;
    
    /*
     * Key counter
     */
    uint64_t _keyCounter;

    /*
     * 2D array containing keys
     */
    std::vector< std::vector <uint64_t> > _keys;

#pragma endregion

#pragma region Main Logic Methods

    /*
     * Generate all keys and count them
     */
    void _GenerateKeys(uint64_t baseStart, uint64_t baseShift)
    {
        uint64_t base{ baseStart };
        uint64_t power{ 2 };

        if (base == 1)
        {
            _keys[(unsigned int) base - 1].push_back(1);
            base += baseShift;
            _keyCounter++;
        }

        /* OUTTER LOOP */
        bool outterWhileCondition{ true };
        while (outterWhileCondition)
        {
            power = 2;

            if (pow(base, power) > _upperLimit ||
                base > _keys.size())
            {
                outterWhileCondition = false;
            }
            else
            {
                /* INNER LOOP */
                bool innerWhileCondition{ true };
                while (innerWhileCondition)
                {
                    uint64_t target = (uint64_t) pow(base, power);

                    if (target >= _lowerLimit)
                    {
                        if (target <= _upperLimit)
                        {
                            _keys[(unsigned int) base - 1].push_back(target);
                            _keyCounter++;
                        }
                        else
                        {
                            innerWhileCondition = false;
                        }
                    }

                    // Get next power number
                    FindNextPrimeNumber(power);
                }

                base += baseShift;
            }
        }
    }

    /*
     * Delete duplicate keys
     * Type: sequential
     */
    void _DeleteDuplicateKeys(void)
    {
        for (unsigned int i{ 0 }; i < _keys.size(); i++)
        {
            for (unsigned int j{ 0 }; j < _keys[i].size(); j++)
            {
                bool condition = true;

                for (unsigned int x{ 0 }; (x <= i && condition); x++)
                {
                    for (unsigned int y{ 0 }; (y < ((x == i) ? j : _keys[x].size()) && condition); y++)
                    {
                        if (i != x && j != y &&
                            _keys[i][j] == _keys[x][y])
                        {
                            _keys[i].erase(_keys[i].begin() + j);
                            j--;

                            _keyCounter--;

                            condition = false;
                            
                        }
                    }
                }
            }
        }

        // Check if any vector is empty
        // If it is, erase it
        for (unsigned int i{ 0 }; i < _keys.size(); i++)
        {
            if (_keys[i].empty())
            {
                _keys.erase(_keys.begin() + i);
                i--;
            }
        }
    }

#pragma endregion

#pragma region Helper Methods

    /*
     * Allocate (push back) vectors
     */
    void _AllocateVectors(void)
    {
        uint64_t target = (uint64_t) sqrt(_upperLimit);

        for (auto i = 0; i < target; i++)
            _keys.push_back(std::vector<uint64_t>());

    }

    /*
     * Find first prime number greater than target
     */
    void FindNextPrimeNumber(uint64_t& number)
    {
        while (!IsPrimeNumber(++number));
    }

    /*
     * Check whether the argument is a prime number
     */
    bool IsPrimeNumber(uint64_t number)
    {
        if (number == 2 || number == 3)
            return true;

        if (number % 2 == 0 || number % 3 == 0)
            return false;

        uint64_t divisor{ 6 };
        while ( ((divisor * divisor) - (2 * divisor) + 1) <= number)
        {
            if ((number % (divisor - 1)) == 0 ||
                (number % (divisor + 1)) == 0)
                return false;

            divisor += 6;
        }

        return true;
    }

#pragma endregion

public:

#pragma region Constructors

    /*
     * Default constructor
     */
    EncryptionKeys(void)
        : _lowerLimit{ 0 }, _upperLimit{ 0 }, _keyCounter{ 0 }
    {
    }

    /*
     * Overloaded constructor
     */
    EncryptionKeys(uint64_t lower, uint64_t upper)
        : _lowerLimit{ lower }, _upperLimit{ upper }, _keyCounter{ 0 }
    {
    }

#pragma endregion

#pragma region Getter and Setter Methods

    /*
     * Limits setter
     */
    void SetLimits(const uint64_t lower, const uint64_t upper)
    {
        SetLowerLimit(lower);
        SetUpperLimit(upper);
    }

    /*
     * Lower limit setter
     */
    void SetLowerLimit(const uint64_t lower)
    {
        _lowerLimit = lower;
    }

    /*
     * Upper limit setter
     */
    void SetUpperLimit(const uint64_t upper)
    {
        _upperLimit = upper;
    }

    /*
    * Reset the key counter and delete all keys
    */
    void ResetKeys(void)
    {
        _keys.clear();
        _keyCounter = 0;
    }

    /*
    * Lower limit getter
    */
    uint64_t GetLowerLimit(void)
    {
        return _lowerLimit;
    }

    /*
    * Upper limit getter
    */
    uint64_t GetUpperLimit(void)
    {
        return _upperLimit;
    }

    /*
    * Key counter getter
    */
    uint64_t GetKeysCount(void)
    {
        return _keyCounter;
    }

#pragma endregion

#pragma region ToString Methods

    /*
     * Wrap all object data in a string
     */
    std::string ToString(void)
    {
        std::stringstream ss;

        ss << LimitsToString();
        ss << CounterToString();
        ss << KeysToString();

        return ss.str();
    }

    /*
    * Wrap limits in a string
    */
    std::string LimitsToString(void)
    {
        std::stringstream ss;

        ss << "Lower limit = " << _lowerLimit << std::endl;
        ss << "Upper limit = " << _upperLimit << std::endl;

        return ss.str();
    }

    /*
    * Wrap counter in a string
    */
    std::string CounterToString(void)
    {
        std::stringstream ss;
        ss << "Number of keys = " << _keyCounter << std::endl;
        return ss.str();
    }

    /*
    * Wrap all keys in a string
    */
    std::string KeysToString(void)
    {
        std::stringstream ss;

        ss << "##################################################" << std::endl;
        ss << "Keys: " << std::endl;

        for (unsigned int i{ 0 }; i < _keys.size(); i++)
        {
            for (unsigned int j{ 0 }; j < _keys[i].size(); j++)
            {
                ss << _keys[i][j] << std::endl;
            }
        }

        return ss.str();
    }

#pragma endregion

#pragma region Init Methods

    /*
     * Initialize the calculation of the keys
     * Type: sequential
     */
    uint64_t Init(void)
    {
        // Check for errors
        if (_lowerLimit < 1 ||
            _upperLimit < 1)
        {
            std::cout << "########## ERROR!!! ##########" << std::endl;
            std::cout << "Lower and/or upper limit is not greater than 1!!!" << std::endl;
            std::cout << "Possible solution: call setter methods to set the limits" << std::endl;

            return 0;
        }

        if (_lowerLimit > _upperLimit)
        {
            std::cout << "########## ERROR!!! ##########" << std::endl;
            std::cout << "Lower limit is greater than upper limit!!!" << std::endl;
            std::cout << "Possible solution: call setter methods to set the limits" << std::endl;

            return 0;
        }

        if (_keyCounter != 0)
        {
            std::cout << "########## ERROR!!! ##########" << std::endl;
            std::cout << "Key counter is not 0!!!" << std::endl;
            std::cout << "Possible solution: call reset counter method to reset the counter and delete all keys" << std::endl;

            return 0;
        }

        // Allocate vectors in advance
        // Not really needed here, but useful for parallel execution
        _AllocateVectors();

        // Start timer
        Timer timer;

        _GenerateKeys(1, 1);
        
        // Stop timer
        uint64_t timePassed = timer.GetTimePassed();
        
        // Delete possible duplicate keys and delete unecessary memory
        _DeleteDuplicateKeys();

        return timePassed;
    }

    /*
     * Initialize the calculation of the keys
     * Type: parallel, using pthreads
     */
    uint64_t InitThread(const int numberOfThreads = 8)
    {
        // Check for errors
        if (_lowerLimit < 1 ||
            _upperLimit < 1)
        {
            std::cout << "########## ERROR!!! ##########" << std::endl;
            std::cout << "Lower and/or upper limit is not greater than 1!!!" << std::endl;
            std::cout << "Possible solution: call setter methods to set the limits" << std::endl;

            return 0;
        }

        if (_lowerLimit > _upperLimit)
        {
            std::cout << "########## ERROR!!! ##########" << std::endl;
            std::cout << "Lower limit is greater than upper limit!!!" << std::endl;
            std::cout << "Possible solution: call setter methods to set the limits" << std::endl;

            return 0;
        }

        if (_keyCounter != 0)
        {
            std::cout << "########## ERROR!!! ##########" << std::endl;
            std::cout << "Key counter is not 0!!!" << std::endl;
            std::cout << "Possible solution: call reset counter method to reset the counter and delete all keys" << std::endl;

            return 0;
        }

        // Allocate vectors in advance
        _AllocateVectors();

        std::thread *threadArr = new std::thread[numberOfThreads];

        // Start timer
        Timer timer;

        for (auto i = 0; i < numberOfThreads; i++)
        {
            threadArr[i] = std::thread (&EncryptionKeys::_GenerateKeys, this, i + 1, numberOfThreads);
        }

        for(auto i = 0; i < numberOfThreads; i++)
        {
            threadArr[i].join();
        }
        
        // Stop timer
        uint64_t timePassed = timer.GetTimePassed();

        // Delete possible duplicate keys and delete unecessary memory
        _DeleteDuplicateKeys();

        delete[] threadArr;

        return timePassed;
    }

    /*
     * Initialize the calculation of the keys
     * Type: parallel, using pthreads
     */
    uint64_t InitCUDA(void)
    {
        // TO DO
        return 0;
    }

#pragma endregion

};
