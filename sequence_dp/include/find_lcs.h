#include <vector>
#include <algorithm>

template <typename Type>
auto findLCS(const std::vector<Type> &seq1, const std::vector<Type> &seq2)
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
    return dp;
}
