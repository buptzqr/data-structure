#ifndef PATH_H
#define PATH_H
#include <iostream>
#include <cassert>
#include <vector>
#include <stack>
// 找到任意两个节点之间的路径
// 深度优先遍历复杂度
// 邻接表o（V+E）
// 邻接矩阵o（V^2）
template <typename Graph>
class Path
{
private:
    Graph &G;
    int s; // source计算从该点到其他节点的路径
    bool *visited;
    int *from; //记录当前节点是从哪个节点遍历过来的
    void dfs(int v)
    {
        visited[v] = true;
        typename Graph::AdjIterator adj(G, v);
        for (int i = adj.begin(); !adj.end(); adj.next())
            if (!visited[i])
            {
                from[i] = v;
                dfs(i);
            }
    }

public:
    Path(Graph &graph, int s)
    {
        assert(s >= 0 && s < G.V());
        visited = new bool[G.V()];
        from = new bool[G.V()];
        for (int i = 0; i < G.V(); i++)
        {
            visited[i] = false;
            from[i] = -1;
        }
        this->s = s;
        // 寻路算法
        dfs(s);
    }
    ~Path()
    {
        delete[] visited;
        delete[] from;
    }
    bool hasPath(int w)
    {
        assert(w >= 0 && w < G.V());
        return visited[w];
    }
    void path(int w, vector<int> &vec)
    {
        stack<int> s;
        int p = w;
        if (!hasPath(w))
            return;
        while (p != -1)
        {
            s.push(p);
            p = from[p];
        }
        vec.clear();
        while (!s.empty())
        {
            vec.push_back(s.top());
            s.pop();
        }
    }
    void showPath(int w)
    {
        vector<int> vec;
        path(w, vec);
        for (auto e : vec)
            cout << e;
    }
};
#endif