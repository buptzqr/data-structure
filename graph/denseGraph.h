#ifndef DESNSEGRAPH_H
#define DESNSEGRAPH_H
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
// 邻接矩阵：用二位矩阵表示图的联通方式
// 连接表：每一行只表示和一个节点相连的其他节点的信息
// 邻接表适合表示一个稀疏的图，邻接矩阵适合表示稠密图
// 因为图中存在环，所以一个额外的字段确认节点是否被遍历
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
    class AdjIterator
    {
    private:
        DenseGraph &G;
        int v;
        int index;

    public:
        AdjIterator(DenseGraph &graph, int v) : G(graph)
        {
            assert(v >= 0 && v < G.n);
            this->v = v;
            this->index = -1;
        }
        int begin()
        {
            index = -1;
            return next();
        }
        // 从当前元素开始找第一个不为false的元素的index
        int next()
        {
            for (index += 1; index < G.g[v].size(); index++)
                if (G.g[v][index])
                    return index;
            return -1;
        }
        bool end()
        {
            return index >= G.V();
        }
    };
};
#endif