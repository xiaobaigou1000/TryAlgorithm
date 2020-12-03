#pragma once
#include <windows.h>
#include <psapi.h>
#include <thread>
#include <chrono>

class ComplexityMeasurement
{
public:
    PROCESS_MEMORY_COUNTERS initialMemoryUsage;
    PROCESS_MEMORY_COUNTERS highestMemoryUsage;
    HANDLE currentProcessHandle;
    bool continueFlag = true;
    std::thread th;

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

    ComplexityMeasurement()
    {
        currentProcessHandle = GetCurrentProcess();
        GetProcessMemoryInfo(currentProcessHandle, &initialMemoryUsage, sizeof(initialMemoryUsage));
        highestMemoryUsage = initialMemoryUsage;
    }

    void measure()
    {
        PROCESS_MEMORY_COUNTERS pmc;
        GetProcessMemoryInfo(currentProcessHandle, &pmc, sizeof(pmc));
        if (pmc.WorkingSetSize > highestMemoryUsage.WorkingSetSize)
        {
            highestMemoryUsage = pmc;
        }
    }

    void run()
    {
        startTime = std::chrono::high_resolution_clock::now();
        auto fun = [this] {
            while (continueFlag)
            {
                measure();
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(10ms);
            }
            endTime = std::chrono::high_resolution_clock::now();
        };
        th = std::move(std::thread(fun));
    }

    void stop()
    {
        continueFlag = false;
        th.join();
    }

    size_t getMemoryUsage()
    {
        return highestMemoryUsage.WorkingSetSize - initialMemoryUsage.WorkingSetSize;
    }

    auto getPassedTime()
    {
        return endTime - startTime;
    }
};