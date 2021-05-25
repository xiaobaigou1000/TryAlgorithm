#include<algorithm>
#include<functional>
#include<spdlog/spdlog.h>
#include<string_view>

//lcs without dp table
int lcs(const std::string& str1, const std::string& str2)
{
	std::function<int(int, int)> dp = [&](int i, int j)->int
	{
		if (i == -1 || j == -1)
			return 0;
		if (str1[i] == str2[j])
			return dp(i - 1, j - 1) + 1;
		else
			return std::max(dp(i - 1, j), dp(i, j - 1));
	};
	return dp(str1.size() - 1, str2.size() - 1);
}

//lcs with dp table and return common sub sequence(still not good)
auto dpLCSWithCommonSequenceOutput(std::string_view str1, std::string_view str2)
{
	std::vector dpTable(str1.size() + 1, std::vector<int>(str2.size() + 1, 0));

	for (size_t i = 0; i < str1.size(); i++)
		for (size_t j = 0; j < str2.size(); j++)
			if (str1[i] == str2[j])
				dpTable[i + 1][j + 1] = dpTable[i][j] + 1;
			else
				dpTable[i + 1][j + 1] = std::max(dpTable[i][j + 1], dpTable[i + 1][j]);

	//construct common sequence output
	std::vector<char> tmp;
	size_t str1Pos = str1.size(), str2Pos = str2.size();
	while (true)
	{
		if (dpTable[str1Pos][str2Pos] == 0)
			break;
		if (dpTable[str1Pos][str2Pos] == dpTable[str1Pos - 1][str2Pos])
		{
			str1Pos -= 1;
			continue;
		}
		if (dpTable[str1Pos][str2Pos] == dpTable[str1Pos][str2Pos - 1])
		{
			str2Pos -= 1;
			continue;
		}
		tmp.push_back(str1[str1Pos - 1]);
		str1Pos -= 1;
		str2Pos -= 1;
	}

	std::string str{ tmp.crbegin(), tmp.crend() };
	return std::make_tuple(dpTable[str1.size()][str2.size()], std::move(str));
}

int main()
{
	using namespace std::string_view_literals;
	auto [size, str] = dpLCSWithCommonSequenceOutput("abcde"sv, "ace"sv);
	spdlog::info("size: {}, str: {}"sv, size, str);
}
