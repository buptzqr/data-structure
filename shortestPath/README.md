# 最短路径问题
对有向图和无向图同样适用  
无向图中的广度优先遍历可以求出无权图的单源最短路径（形成一个最短路径树）
## 松弛操作（求最短路径的核心）
对于到一个节点的最短路径，我们要看一下从原始节点到新加入的节点再加上新加入的节点到该节点的路径，是否比原始的节点到该节点的路径短  
## dijkstra算法（单源最短路径算法）
- 前提：图中不能有负权边
- 时间复杂度：Elog（V）
- 实现思路：既要找到最值，又要更新列表，因此使用min index heap来实现
## Bellman-Ford算法（单源最短路径算法）
- 前提：不能有负权环（拥有负权环的图没有最短路径，应为其他节点可以绕此环，每绕一次路径就变短）
- 可以判断图中是否有负权环
- 复杂度o（EV）
- 思想：如果一个图没有负权环，从一点到另外一点的最短路径，最多经过所有的V个顶点，有V-1条边；否则，存在顶点经过了两次，即存在负权环
- 对一个点的一次松弛操作，就是找到经过这个点的另外一条路径，多一条边，权值更小
- 如果一个图没有负权环，从一点到另外一点的最短路径，最多经过所有的V个顶点，有V-1条边
- 对所有的点进行V-1次操作


