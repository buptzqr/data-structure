// 可以非常高效的解决连接问题
// 网络中的连接状态
// 数学中集合类的实现
// 连接问题比路径问题回答的东西要少
// 对于一组数据主要支持两个操作：union(p,q)将两个元素连接起来，find(p)找到元素在哪个组中
// isConnected(p,q)两个元素是否连接
// 连接在一起的元素具有相同的id号
#ifndef UNIONFIND_V1_H
#define UNIONFIND_V1_H
#include <iostream>
#include <cassert>
using namespace std;
class UnionFindV1
{
private:
    int *id;
    int count;

public:
    UnionFindV1(int n)
    {
        count = n;
        id = new int[n];
        for (int i = 0; i < n; i++)
        {
            id[i] = i;
        }
    }
    ~UnionFindV1()
    {
        delete[] id;
    }
    // quick find
    // o(1)
    int find(int p)
    {
        assert(p >= 0 && p < count);
        return id[p];
    }
    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
    }
    // o(n)
    void unionElement(int p, int q)
    {
        int pId = find(p);
        int qId = find(q);
        if (pId == qId)
            return;
        for (int i = 0; i < count; i++)
            if (id[i] == pId)
                id[i] = qId;
    }
};
#endif