#ifndef COMPONENT_H
#define COMPONENT_H
#include <iostream>
#include <cassert>
using namespace std;
// 用来求联通分量

template <typename Graph>
class Component
{
private:
    Graph &G;
    bool *visited;
    int ccount; //统计有多少联通分量
    int id;     //和并查集一样，相连的节点取相同的id

    void dfs(int v)
    {
        visited[v] = true;
        id[v] = ccount;
        typename Graph::AdjIterator adj(G, v);
        for (int i = adj.begin(); !adj.end(); adj.next())
            if (!visited[i])
                dfs(i);
    }

public:
    Component(Graph &graph) : G(graph)
    {
        visited = new bool[G.V()];
        id = new int[G.V()];
        ccount = 0;
        for (int i = 0; i < G.V(); i++)
        {
            visited[i] = false;
            id[i] = -1; //我觉得等于i会比较合适
        }
        for (int i = 0; i < G.V(); i++)
        {
            if (!visited[i])
            {
                dfs(i);
                ccount++;
            }
        }
    }
    ~Component()
    {
        delete[] visited;
        delete[] id;
    }
    int count() { return ccount; }
    bool isConnected(int v, int w)
    {
        assert(v >= 0 && v < G.V());
        assert(w >= 0 && w < G.V());
        return id[v] == id[w];
    }
};

#endif