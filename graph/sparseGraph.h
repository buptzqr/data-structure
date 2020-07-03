#ifndef SPARSE_GRAPH
#define SPARSE_GRAPH
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
class SparseGraph
{
private:
    int n, m;
    bool directed;
    vector<vector<int>> g;

public:
    SparseGraph(int n, bool directed)
    {
        this->n = n;
        this->m = 0;
        this->directed = directed;
        for (int i = 0; i < n; i++)
            g.push_back(vector<int>());
    }
    ~SparseGraph() {}
    int V() { return n; }
    int E() { return m; }
    void addEdge(int v, int w)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        g[v].push_back(w);
        if (v != w && !directed) //v!=w是为了去除自环边
            g[w].push_back(v);
        m++;
    }
    // 就是为了取消平行边，时间复杂度是o（n），所以不添加取消平行边的操作
    // 但是要记住这是邻接表的一个缺陷
    bool hasEdge(int v, int w)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        for (int i = 0; i < g[v].size(); i++)
        {
            if (g[v][i] == w)
                return false;
        }
        return true;
    }
};
#endif