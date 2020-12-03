#pragma once
#include <iterator>
#include <vector>
#include <algorithm>


template<typename Type>
size_t findLCS(const std::vector<Type>& seq1, const std::vector<Type>& seq2)
{
    std::vector<std::vector<size_t>> dp(seq1.size() + 1, std::vector<size_t>(seq2.size() + 1, 0));

    for (size_t i = 1; i <= seq1.size(); i++)
    {
		for (size_t j = 1; j <= seq2.size(); j++)
        {
            if (seq1[i - 1] == seq2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    for (const auto& line : dp)
    {
        for (auto e : line)
        {
            std::cout << e << '\t';
        }
        std::cout << std::endl;
    }

    return dp.back().back();
}

template <typename Iter, typename Type = typename std::iterator_traits<Iter>::value_type>
std::vector<Type> findLIS(Iter begin, Iter end)
{
    size_t seq_len = end - begin;

    // [ ( max_length, last_elem ), ... ]
    std::vector<std::pair<size_t, size_t>> dp(seq_len);

    dp[0] = {1, 0};

    for (size_t i = 1; i < seq_len; i++)
    {
        size_t max_len = 0;
        size_t last_elem = 0;
        for (size_t j = 0; j < i; j++)
        {
            if (*(begin + j) < *(begin + i) && max_len < dp[j].first)
            {
                max_len = dp[j].first;
                last_elem = j;
            }
        }
        dp[i] = {max_len + 1, last_elem};
    }

    auto last_pair = std::max_element(dp.begin(), dp.end(), [](auto left, auto right) { return left.first < right.first; });
    auto pair_index = last_pair - dp.begin();

    std::vector<Type> lis((*last_pair).first);

    for (int i = lis.size() - 1; i >= 0; i--)
    {
        lis[i] = *(begin + pair_index);
        pair_index = dp[pair_index].second;
    }

    return lis;
}