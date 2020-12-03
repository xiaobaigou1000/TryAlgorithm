#include "find_lcs.h"
#include <iostream>
#include <cassert>

int main()
{
    std::string str1 = "abcde";
    std::string str2 = "ace";

    std::vector<char> seq1{str1.begin(), str1.end()};
    std::vector<char> seq2{str2.begin(), str2.end()};

    auto result = findLCS(seq1, seq2);

    for (auto &i : result)
    {
        for (auto &j : i)
        {
            std::cout << j << ' ';
        }
        std::cout << std::endl;
    }
    assert(result.back().back() == 3);
}
