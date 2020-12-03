#pragma once
#include <deque>
#include <vector>
#include <algorithm>
#include <ostream>
#include <chrono>
#include <random>
#include <iomanip>
#include <iterator>
#include <functional>
#include <numeric>
#include <future>

#include "FoolAVL.h"
#include "SequenceMemoryAVL.h"
namespace FoolSort
{
    template <class DataTraits>
    inline void swapElement(DataTraits a, DataTraits b)
    {
        typename std::iterator_traits<DataTraits>::value_type tmp = *a;
        *a = *b;
        *b = tmp;
    }

    template <class Data>
    std::vector<Data> inplace_AVLSort(std::vector<Data> &toSort)
    {
        FoolAVL<Data> sortAVL;
        for (auto i : toSort)
        {
            sortAVL.insert(i);
        }
        size_t i = 0;
        sortAVL.inOrderTraverse([&toSort, &i](auto val) { toSort[i]=val;++i; });
        return toSort;
    }

    template <class Data>
    std::vector<Data> AVLSort(std::vector<Data> toSort)
    {
        FoolAVL<Data> sortAVL;
        for (auto i : toSort)
        {
            sortAVL.insert(i);
        }
        toSort.clear();
        sortAVL.inOrderTraverse([&toSort](auto i) { toSort.push_back(i); });
        return toSort;
    }

    template <class RandomIte>
    void maxHeapify(RandomIte begin, RandomIte start, RandomIte end)
    {
        auto father = start;
        auto son = begin + 2 * (father - begin) + 1;
        while (son < end)
        {
            if (son + 1 < end && *son < *(son + 1))
            {
                ++son;
            }
            if (*father > *son)
                return;
            else
            {
                std::iter_swap(father, son);
                father = son;
                son = begin + 2 * (father - begin) + 1;
            }
        }
    }

    template <class Data>
    std::vector<Data> heapSort(std::vector<Data> toSort)
    {
        auto begin = toSort.begin();
        auto end = toSort.end();
        auto length = toSort.size();
        for (auto i = begin + length / 2 - 1; i != begin - 1; --i)
        {
            maxHeapify(begin, i, end);
        }
        for (auto i = end - 1; i != begin; --i)
        {
            std::iter_swap(begin, i);
            maxHeapify(begin, begin, i);
        }
        return std::move(toSort);
    }

    template <class Data>
    void inplace_heapSort(std::vector<Data> &toSort)
    {
        auto begin = toSort.begin();
        auto end = toSort.end();
        auto length = toSort.size();
        for (auto i = begin + length / 2 - 1; i != begin - 1; --i)
        {
            maxHeapify(begin, i, end);
        }
        for (auto i = end - 1; i != begin; --i)
        {
            std::iter_swap(begin, i);
            maxHeapify(begin, begin, i);
        }
    }

    template <class RandomIte>
    RandomIte quicksortPartion(RandomIte low, RandomIte high)
    {
        auto leftPointer = low;
        auto rightPointer = high + 1;
        auto partionValue = *low;
        while (true)
        {
            while (*++leftPointer < partionValue)
                if (leftPointer == high)
                    break;
            while (partionValue < *--rightPointer)
                if (rightPointer == low)
                    break;
            if (leftPointer >= rightPointer)
                break;
            std::iter_swap(leftPointer, rightPointer);
        }
        std::iter_swap(low, rightPointer);
        return rightPointer;
    }

    template <class RandomIte>
    void quickSortSub(RandomIte low, RandomIte high)
    {
        if (high <= low)
            return;
        RandomIte partionPoint = quicksortPartion(low, high);
        quickSortSub(low, partionPoint - 1);
        quickSortSub(partionPoint + 1, high);
    }

    template <class Data>
    std::vector<Data> quickSort(std::vector<Data> toSort)
    {
        quickSortSub(toSort.begin(), toSort.end() - 1);
        return std::move(toSort);
    }

    template <class Data>
    void inplace_quickSort(std::vector<Data> &toSort)
    {
        quickSortSub(toSort.begin(), toSort.end() - 1);
    }

    template <class Data>
    std::vector<Data> bubbleSort(std::vector<Data> toSort)
    {
        auto begin = std::begin(toSort);
        auto beforEnd = std::end(toSort) - 1;
        for (auto i = begin; i != beforEnd; i++)
        {
            for (auto j = begin; j != begin + (beforEnd - i); ++j)
            {
                if (*j > *(j + 1))
                {
                    std::iter_swap(j, j + 1);
                }
            }
        }
        return std::move(toSort);
    }

    template <class Data>
    void inplace_bubbleSort(std::vector<Data> &toSort)
    {
        auto begin = std::begin(toSort);
        auto beforEnd = std::end(toSort) - 1;
        for (auto i = begin; i != beforEnd; i++)
        {
            for (auto j = begin; j != begin + (beforEnd - i); ++j)
            {
                if (*j > *(j + 1))
                {
                    std::iter_swap(j, j + 1);
                }
            }
        }
    }

    template <class Data>
    std::vector<Data> simpleSelectSort(std::vector<Data> toSort)
    {
        auto begin = toSort.begin();
        auto end = toSort.end();
        for (auto i = begin; i != end; ++i)
        {
            auto min = std::min_element(i, end);
            if (min != i)
                std::iter_swap(i, min);
        }
        return std::move(toSort);
    }

    template <class Data>
    std::vector<Data> insertSort(std::vector<Data> toSort)
    {
        toSort.push_back(Data());
        auto backSentry = std::rbegin(toSort);
        auto reverseBegin = std::rbegin(toSort);
        auto reverseEnd = std::rend(toSort);

        for (auto i = reverseBegin + 2; i != reverseEnd; ++i)
        {
            *backSentry = *i;
            for (auto j = i; *j > *(j - 1); --j)
            {
                std::iter_swap(j, j - 1);
            }
        }
        toSort.pop_back();
        return std::move(toSort);
    }

    template <typename Data>
    void inplace_insert_sort(std::vector<Data> &toSort)
    {
        toSort.push_back(Data());
        auto backSentry = std::rbegin(toSort);
        auto reverseBegin = std::rbegin(toSort);
        auto reverseEnd = std::rend(toSort);

        for (auto i = reverseBegin + 2; i != reverseEnd; ++i)
        {
            *backSentry = *i;
            for (auto j = i; *j > *(j - 1); --j)
            {
                std::iter_swap(j, j - 1);
            }
        }
        toSort.pop_back();
    }

    template <class Data>
    std::vector<Data> binaryInsertionSort(std::vector<Data> toSort)
    {
        toSort.push_back(Data());
        auto backSentry = std::rbegin(toSort);
        auto reverseBegin = std::rbegin(toSort);
        auto reverseEnd = std::rend(toSort);
        typename std::vector<Data>::reverse_iterator reverseLow, reverseHigh, reverseMiddle;
        for (auto i = reverseBegin + 2; i != reverseEnd; ++i)
        {
            *backSentry = *i;
            reverseLow = reverseBegin + 1;
            reverseHigh = i - 1;
            while (reverseLow <= reverseHigh)
            {
                reverseMiddle = (reverseLow + (reverseHigh - reverseLow) / 2);
                if (*backSentry < *reverseMiddle)
                    reverseLow = reverseMiddle + 1;
                else
                    reverseHigh = reverseMiddle - 1;
            }
            for (auto j = i - 1; j > reverseHigh; --j)
            {
                *(j + 1) = *j;
            }
            *(reverseHigh + 1) = *backSentry;
        }
        toSort.pop_back();
        return std::move(toSort);
    }

    template <class Data>
    void inplace_binaryInsertionSort(std::vector<Data> &toSort)
    {
        toSort.push_back(Data());
        auto backSentry = std::rbegin(toSort);
        auto reverseBegin = std::rbegin(toSort);
        auto reverseEnd = std::rend(toSort);
        typename std::vector<Data>::reverse_iterator reverseLow, reverseHigh, reverseMiddle;
        for (auto i = reverseBegin + 2; i != reverseEnd; ++i)
        {
            *backSentry = *i;
            reverseLow = reverseBegin + 1;
            reverseHigh = i - 1;
            while (reverseLow <= reverseHigh)
            {
                reverseMiddle = (reverseLow + (reverseHigh - reverseLow) / 2);
                if (*backSentry < *reverseMiddle)
                    reverseLow = reverseMiddle + 1;
                else
                    reverseHigh = reverseMiddle - 1;
            }
            for (auto j = i - 1; j > reverseHigh; --j)
            {
                *(j + 1) = *j;
            }
            *(reverseHigh + 1) = *backSentry;
        }
        toSort.pop_back();
    }

    template <class Data>
    std::vector<Data> shellSort(std::vector<Data> toSort)
    {
        auto begin = std::begin(toSort);
        auto end = std::end(toSort);
        int dk = 1;
        while (dk < (end - begin) / 3)
            dk = 3 * dk + 1;
        while (dk > 0)
        {
            for (auto i = begin + dk; i != end; ++i)
            {
                for (auto j = i; (j - begin) >= dk && *j < *(j - dk); j -= dk)
                {
                    std::iter_swap(j, j - dk);
                }
            }
            dk /= 3;
        }
        return std::move(toSort);
    }

    template <class Data>
    void inplace_shellSort(std::vector<Data> &toSort)
    {
        auto begin = std::begin(toSort);
        auto end = std::end(toSort);
        int dk = 1;
        while (dk < (end - begin) / 3)
            dk = 3 * dk + 1;
        while (dk > 0)
        {
            for (auto i = begin + dk; i != end; ++i)
            {
                for (auto j = i; (j - begin) >= dk && *j < *(j - dk); j -= dk)
                {
                    std::iter_swap(j, j - dk);
                }
            }
            dk /= 3;
        }
    }

    template <class RandomIte>
    inline void mergeSub(RandomIte low, RandomIte middle, RandomIte high, RandomIte tempArrayBeginPosition)
    {
        std::copy(low, high, tempArrayBeginPosition);
        auto firstHalfIte = tempArrayBeginPosition;
        auto lastHalfIte = tempArrayBeginPosition + (middle - low);
        auto newMiddle = lastHalfIte;
        auto newHigh = tempArrayBeginPosition + (high - low);
        for (auto i = low; i != high; ++i)
        {
            if (firstHalfIte == newMiddle)
            {
                *i = *lastHalfIte++;
            }
            else if (lastHalfIte == newHigh)
            {
                *i = *firstHalfIte++;
            }
            else if (*lastHalfIte < *firstHalfIte)
            {
                *i = *lastHalfIte++;
            }
            else
            {
                *i = *firstHalfIte++;
            }
        }
    }

    template <class RandomIte>
    void mergeSortSub(RandomIte low, RandomIte high, RandomIte tempArrayBeginPosition)
    {
        if ((high - 1) == low)
            return;
        auto middle = low + (high - low) / 2;
        mergeSortSub(low, middle, tempArrayBeginPosition);
        mergeSortSub(middle, high, tempArrayBeginPosition);
        mergeSub(low, middle, high, tempArrayBeginPosition);
    }

    template <class Data>
    std::vector<Data> mergeSort(std::vector<Data> toSort)
    {
        auto begin = std::begin(toSort);
        auto end = std::end(toSort);
        std::vector<Data> tempArray;
        tempArray.resize(toSort.size());
        mergeSortSub(std::begin(toSort), std::end(toSort), std::begin(tempArray));
        return std::move(toSort);
    }

    template <class Data>
    void inplace_mergeSort(std::vector<Data> &toSort)
    {
        auto begin = std::begin(toSort);
        auto end = std::end(toSort);
        std::vector<Data> tempArray;
        tempArray.resize(toSort.size());
        mergeSortSub(std::begin(toSort), std::end(toSort), std::begin(tempArray));
    }

    template <class Data>
    std::vector<Data> spawnOriginData(long long size)
    {
        std::default_random_engine dre(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<Data> uid(0, 1000000000);
        std::vector<Data> ret;
        for (size_t i = 0; i < size; i++)
        {
            ret.push_back(uid(dre));
        }
        return std::move(ret);
    }

    template <class Data>
    std::ostream &operator<<(std::ostream &out, std::vector<Data> toPrint)
    {
        for (int i = 0; i < 100; ++i)
        {
            out << std::setw(12) << toPrint[i];
            if ((i + 1) % 10 == 0)
            {
                out << '\n';
            }
        }
        return out;
    }

    template <class Data>
    std::vector<Data> getReferenceSortedArray(std::vector<Data> input)
    {
        std::sort(std::begin(input), std::end(input));
        return std::move(input);
    }

    std::chrono::duration<double, std::nano> sortTimeCaculation(std::vector<int> (*sortFunction)(std::vector<int>), const std::vector<int> &toSort, std::vector<int> &sorted)
    {
        std::vector<std::future<std::chrono::steady_clock::duration>> algorithmTests;
        std::vector<std::chrono::steady_clock::duration> testTimes;
        std::chrono::high_resolution_clock hrc;
        auto beforSort = hrc.now();

        auto algorithmTimer = [&hrc, &toSort, sortFunction]() {
            auto beforSort = hrc.now();
            sortFunction(toSort);
            return hrc.now() - beforSort;
        };

        for (size_t i = 0; i < 5; i++)
        {
            algorithmTests.push_back(std::async(algorithmTimer));
        }
        sorted = sortFunction(toSort);
        for (auto &i : algorithmTests)
        {
            testTimes.push_back(i.get());
        }
        auto ambigousTime = std::accumulate(std::begin(testTimes), std::end(testTimes), std::chrono::steady_clock::duration());
        ambigousTime /= testTimes.size();
        auto actualTime = ambigousTime * 0.4;
        algorithmTests.clear();

        for (size_t i = 0; i < 6; i++)
        {
            algorithmTests.push_back(std::async(algorithmTimer));
        }
        for (auto &i : algorithmTests)
        {
            testTimes.push_back(i.get());
        }
        ambigousTime = std::accumulate(std::begin(testTimes), std::end(testTimes), std::chrono::steady_clock::duration());
        ambigousTime /= testTimes.size();
        actualTime += ambigousTime * 0.6;
        return actualTime;
    }

    void sortFunctionTestAndEfficiencyComparison(std::ostream &out, long long sampleSize, std::vector<int> (*sortFunction)(std::vector<int>))
    {
        auto toSort = spawnOriginData<int>(sampleSize);
        std::chrono::high_resolution_clock hrc;
        auto beforSort = hrc.now();

        std::vector<int> referenceSorted;
        auto averageReferenceTime = sortTimeCaculation(getReferenceSortedArray, toSort, referenceSorted);
        std::vector<int> sorted;
        auto averageAlgorithmTime = sortTimeCaculation(sortFunction, toSort, sorted);

        out << "\ttest of " << toSort.size() << " samples.\n";
        out << "\taverage time of 11 times sort.\n\n";
        out << "first 100 element of origin random vector:\n\n";
        out << toSort;
        out << "\n\n";

        out << "first 100 element of reference sorted array:\n\n";
        out << referenceSorted;
        out << "\n\n";
        out << "average time used in std::sort function: " << (long long)averageReferenceTime.count() << " ns.\n\n";

        out << "first 100 element of sorted array by sort function:\n\n";
        out << sorted << "\n\n";
        out << "average time used in user defined sort function: " << (long long)averageAlgorithmTime.count() << " ns.\n\n";
    }
} // namespace FoolSort