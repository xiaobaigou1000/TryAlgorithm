#include "foolsort.h"
#include "space_complexity.h"

int main()
{
    calculateSpaceComplexity(50000, 10000, 200, 1, "hello.txt", FoolSort::AVLSort<size_t>);

    std::vector<uint32_t> hello{10000000};

    HANDLE currentProcessHandle = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS initialMemoryUsage;
    GetProcessMemoryInfo(currentProcessHandle, &initialMemoryUsage, sizeof(initialMemoryUsage));
    spdlog::info("current process memory usage: {} bytes", initialMemoryUsage.WorkingSetSize);
}
