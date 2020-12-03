#include "foolsort.h"
#include <spdlog/spdlog.h>
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include <mutex>
#include <thread>
#include <fstream>
#include<chrono>

class MemoryMesurement
{
public:
    PROCESS_MEMORY_COUNTERS initialMemoryUsage;
    PROCESS_MEMORY_COUNTERS highestMemoryUsage;
    HANDLE currentProcessHandle;
    bool continueFlag = true;
    std::thread th;

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

    MemoryMesurement()
    {
        currentProcessHandle = GetCurrentProcess();
        GetProcessMemoryInfo(currentProcessHandle, &initialMemoryUsage, sizeof(initialMemoryUsage));
        highestMemoryUsage = initialMemoryUsage;
        spdlog::info("initial process memory usage: {} bytes", initialMemoryUsage.WorkingSetSize);
    }

    void measure()
    {
        PROCESS_MEMORY_COUNTERS pmc;
        GetProcessMemoryInfo(currentProcessHandle, &pmc, sizeof(pmc));
        if (pmc.WorkingSetSize > highestMemoryUsage.WorkingSetSize)
        {
            highestMemoryUsage = pmc;
        }
        // spdlog::info("current process memory usage: {} bytes", pmc.WorkingSetSize);
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
        printMaxMemoryUsage();
    }

    void printMaxMemoryUsage()
    {
        spdlog::info("peek memory: {}", highestMemoryUsage.WorkingSetSize);
    }
};

template <typename SortFunc>
void calculateSpaceComplexity(const size_t InitialDatasetSize, const size_t step, const size_t iterTimes, const size_t repeatTimes, const std::string &fileName, SortFunc func)
{
    size_t currentSize = InitialDatasetSize;

    std::ofstream ofile(fileName + ".csv");

    for (size_t i = 0; i < iterTimes; i++)
    {
        std::vector<size_t> rawArray = FoolSort::spawnOriginData<size_t>(currentSize);

        MemoryMesurement mm;
        mm.run();

        for (size_t j = 0; j < repeatTimes; j++)
        {
            spdlog::info("current dataset size: {}, iteration time: {}", currentSize, j + 1);
            func(rawArray);
            std::random_shuffle(rawArray.begin(), rawArray.end());
        }

        mm.stop();
        std::string str = fmt::format("{},{}\n", currentSize, mm.highestMemoryUsage.WorkingSetSize - mm.initialMemoryUsage.WorkingSetSize);
        ofile << str;
        currentSize += step;
    }
}
