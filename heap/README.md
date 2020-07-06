# 堆
## 主要操作
- shiftdown
- shiftup
- heapify：从非叶节点开始进行shitdown操作，从而得到最大堆
- change：改变一个节点的值，同时维护堆的性质，进行一次shiftdown，一次shiftup操作就行
## 索引堆
### 普通堆的缺陷
- 原本构建heap要交换大量的元素，这种交换的性能损耗比较大
- 元素位置发生改变，导致无法进行索引
### 要点
- 索引堆构建堆的元素是索引
- data的存储位置没有发生改变
- 元素比较的时候比的是data，元素交换的时候，交换的是索引
- 一个关键点就是记住indexes的内容是元素的索引，indexes的索引是元素在堆中的位置
- reverse表示索引i在堆中的位置 也就是index[j] = i reverse[i] = j indexes[reverse[i]]=i reverse[indexes[i]]=i
- reverse这个技术叫反向查找技术