#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
private:
    vector<int> parent;
    int part = 0;

public:
    struct Edge
    {
        int a, b, w;
        bool operator<(const Edge &e) const
        {
            return w < e.w;
        }
    };

    int minCostConnectPoints(vector<vector<int>> &points)
    {
        int n = points.size();
        if (n <= 1)
            return 0;
        //connections每一行是两个顶点和权重
        vector<Edge> connections;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                connections.push_back({i, j,
                                       abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])});
            }
        }
        return minimumCost(n, connections);
    }

    int minimumCost(int n, vector<Edge> &connections)
    {
        part = n;
        parent = vector<int>(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
        //把所有边按权值进行排序
        sort(connections.begin(), connections.end());
        int res = 0;
        for (Edge &conn : connections)
        {
            int pa = find(conn.a);
            int pb = find(conn.b);
            if (pa != pb)
            {
                uni(conn.a, conn.b);
                res += conn.w;
            }
            if (part == 1)
                return res;
        }
        return -1;
    }
    int find(int a)
    {
        if (parent[a] == a)
            return a;
        parent[a] = find(parent[a]);
        return parent[a];
    }
    void uni(int a, int b)
    {
        int pa = find(a);
        int pb = find(b);
        if (pa == pb)
            return;
        parent[pa] = pb;
        part--;
    }
};

int main()
{
    vector<vector<int>> a{{-1000000,-1000000},{1000000,1000000}};
    Solution s;
    std::cout << s.minCostConnectPoints(a) << std::endl;
}