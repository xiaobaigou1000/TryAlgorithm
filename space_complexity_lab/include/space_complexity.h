#include "foolsort.h"
#include <spdlog/spdlog.h>
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include <mutex>
#include <thread>

class MemoryMesurement
{
public:
    PROCESS_MEMORY_COUNTERS initialMemoryUsage;
    std::vector<PROCESS_MEMORY_COUNTERS> memoryUsages;
    HANDLE currentProcessHandle;
    bool continueFlag = true;
    std::thread th;

    MemoryMesurement()
    {
        currentProcessHandle = GetCurrentProcess();
        GetProcessMemoryInfo(currentProcessHandle, &initialMemoryUsage, sizeof(initialMemoryUsage));
        spdlog::info("initial process memory usage: {} bytes", initialMemoryUsage.WorkingSetSize);
    }

    void measure()
    {
        PROCESS_MEMORY_COUNTERS pmc;
        GetProcessMemoryInfo(currentProcessHandle, &pmc, sizeof(pmc));
        memoryUsages.push_back(pmc);
        // spdlog::info("current process memory usage: {} bytes", pmc.WorkingSetSize);
    }

    void run()
    {
        auto fun = [this] {
            while (continueFlag)
            {
                measure();
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(100ms);
            }
        };
        th = std::move(std::thread(fun));
    }

    void printMaxMemoryUsage()
    {
        auto maxPhysicMemory = *std::max_element(memoryUsages.begin(), memoryUsages.end(), [](auto l, auto r) { return l.WorkingSetSize < r.WorkingSetSize; });
        spdlog::info("peek memory: {}", maxPhysicMemory.WorkingSetSize);
    }
};

template <typename SortFunc>
void calculateSpaceComplexity(const size_t InitialDatasetSize, const size_t step, const size_t iterTimes, const size_t repeatTimes, const std::string &fileName, SortFunc func)
{
    size_t currentSize = InitialDatasetSize;

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
        currentSize += step;

        mm.continueFlag = false;
        mm.th.join();
        mm.printMaxMemoryUsage();
    }
}
