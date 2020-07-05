# 并查集
## 并查集可以方便的得知两个节点是否相连，解决连接问题
## 基本操作
### find:查找一个节点属于哪个集合
### isConnected:判断两个节点是否相连
### unionElement:将两个节点放入统一集合中
## 基本思路
### quickfind思路：用一个id数组来记录节点所属的集合，id的索引代表节点本身，id的值代表节点所属的集合
>#### quickFind思路可以以o（1）的复杂度得到节点所属的组（是否相连）
### parent思路：用一个parent数组来记录该节点的父亲节点，parent的索引代表节点本身，parent的值代表节点所属的集合
### 优化一：用sz数组来记录节点所属的集合总共有多少节点，每次uinon时，将节点总数小的集合连接到总数大的集合
### 优化二：基于rank的优化，rank[i]表示根节点为i的树的高度,将层数少的集合指向层数大的集合（并查集常规实现）
>### 这两个优化是在unionElement操作时进行的
### 优化三：路径压缩
>### 基本式：
```
int find(int p)
    {
        assert(p >= 0 && p < count);
        while (p != parent[p])
        {
            p = parent[p];
        }
        return p;
    }
```
>### 跳跃式：
```
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
```
>### 直接压缩成两层：
```
    int findV3(int p)
    {
        assert(p >= 0 && p < count);
        if (p != parent[p])
            parent[p] = findV3(parent[p]);
        return parent[p];
    }
```
>### 这两个优化是在find操作时进行的