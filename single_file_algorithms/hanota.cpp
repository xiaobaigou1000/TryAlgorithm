#include<vector>
#include<spdlog/spdlog.h>

void hanota(size_t n,std::vector<int>& A, std::vector<int>& B, std::vector<int>& C)
{
    
    if (n == 1)
    {
        C.push_back(A.back());
        A.pop_back();
        return;
    }
    else
    {
        hanota(n - 1, A, C, B);
        C.push_back(A.back());
        A.pop_back();
        hanota(n - 1, B, A, C);
    }
}

int main()
{
    std::vector<int> First(4,0);
    std::vector<int> Second, Third;
    hanota(First.size(), First, Second, Third);
    return 0;
}