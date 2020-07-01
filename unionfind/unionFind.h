// 将每个元素看成一个节点，每个节点有一个指针指向他的父亲
// 优化以后并查集的操作近乎都是o（1）
#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <iostream>
#include <cassert>
using namespace std;
class UnionFind
{
private:
    int *parent;
    int count;
    int *sz;   //sz[i]表示以i为根的集合中有多少元素
    int *rank; //rank[i]表示以i为根的集合所表示的树的层数，和上面的sz有一个就行

public:
    UnionFindV1(int n)
    {
        count = n;
        parent = new int[n];
        sz = new int[n];
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            sz[i] = 1;
            rank[i] = 1;
        }
    }
    ~UnionFindV1()
    {
        delete[] parent;
        delete[] sz;
        delete[] rank;
    }
    int find(int p)
    {
        assert(p >= 0 && p < count);
        while (p != parent[p])
        {
            p = parent[p];
        }
        return p;
    }
    int findV1(int p)
    {
        assert(p >= 0 && p < count);
        while (p != parent[p])
        {
            // 路径压缩
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p;
    }
    // 直接压缩成两层
    int findV3(int p)
    {
        assert(p >= 0 && p < count);
        if (p != parent[p])
            parent[p] = findV3(parent[p]);
        return parent[p];
    }
    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
    }
    void unionElement(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);
        if (pRoot == qRoot)
            return;
        // 优化1：存储每个集合的元素数量，将元素少的集合的根节点指向元素多的集合的根节点
        if (sz[pRoot] < sz[qRoot])
        {
            parent[pRoot] = qRoot;
            sz[qRoot] += sz[pRoot];
        }
        else
        {
            parent[qRoot] = pRoot;
            sz[pRoot] += sz[qRoot];
        }
    }
    // 优化2：基于rank的优化，rank[i]表示根节点为i的树的高度,将层数少的集合指向层数大的集合
    void unionElementV2(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);
        if (p == qRoot)
            return;
        if (rank[pRoot] < rank[qRoot])
        {
            parent[pRoot] = qRoot;
        }
        else if (rank[pRoot] > rank[qRoot])
        {
            parent[qRoot] = pRoot;
        }
        else
        {
            parent[qRoot] = pRoot;
            rank[pRoot] += 1;
        }
    }
    // 优化3：路径压缩
};
#endif