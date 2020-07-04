#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H
#include <iostream>
#include <queue>
// 广度优先遍历复杂度
// 邻接表o（V+E）
// 邻接矩阵o（V^2）
// 使用广度优先遍历来解决这个问题
template <typename Graph>
class ShortestPath
{
private:
    Graph &G;
    int s;
    bool *visited;
    int *from;
    int *ord; //记录s到任意节点的最短距离是多少
public:
    ShortestPath(Graph &graph, int s) : G(graph)
    {
        assert(s >= 0 && s < G.V());
        this->s = s;
        visited = new int[G.V()];
        from = new int[G.V()];
        ord = new int[G.V()];
        for (int i = 0; i < G.V(); i++)
        {
            visited[i] = false;
            from[i] = -1;
            ord[i] = -1;
        }
        // 一旦进入队列visited就置为true
        queue<int> q;
        q.push(s);
        visited[s] = true;
        ord[s] = 0;
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            typename Graph::AdjIterator adj(G, v); //这里是为了让编译器知道AdjIterator是类里面的一个类型
            for (int i = adj.begin(); !adj.end(); adj.next())
                if (!visited[i])
                {
                    q.push(i);
                    visited[i] = true;
                    from[i] = v;
                    ord[i] = ord[v] + 1;
                }
        }
    }
    ~ShortestPath()
    {
        delete[] visited;
        delete[] from;
        delete[] ord;
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
    int length(int w)
    {
        assert(w >= 0 && w < G.V());
        return ord[w];
    }
};
#endif