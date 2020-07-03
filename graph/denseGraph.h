#ifndef DESNSEGRAPH_H
#define DESNSEGRAPH_H
#include <iostream>
#include <vector>
#include <assert>
using namespace std;
// 邻接矩阵：用二位矩阵表示图的联通方式
// 连接表：每一行只表示和一个节点相连的其他节点的信息
// 邻接表适合表示一个稀疏的图，邻接矩阵适合表示稠密图
class DenseGraph
{
private:
    int n, m; // 表示节点和边
    bool directed;
    vector<vector<bool>> g;

public:
    DenseGraph(int n, bool directed)
    {
        this->n = n;
        this->m = 0;
        this->directed = directed;
        for (int i = 0; i < n; i++)
            g.push_back(vector<bool>(n, false));
    }
    ~DenseGraph() {}
    int V() { return n; }
    int E() { return m; }
    bool addEdge(int v, int w)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        // 这个地方判断是为了防止下面的m++在有边是多加1
        if (hasEdge(v, w))
            return;
        g[v][w] = 1;
        if (!directed)
            g[w][v] = 1;
        m++;
    }
    bool hasEdge(int v, int w)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        return g[v][w];
    }
};
#endif