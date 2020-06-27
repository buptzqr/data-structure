#ifndef HEAP_H
#define HEAP_H
// 二叉堆的性质：子节点的数值都不大于父节点，堆是一个完全二叉树（即除了最后一层，其他层都是满的
// 最后一层所有节点集中在左侧），这叫做最大堆，相应的可以自己理解最小堆
// 可以用数组存储二叉堆，因为堆是一个完全二叉树
// 从一开始标记堆
#include <iostream>
#include <cassert>
template <typename Item>
class MaxHeap
{
private:
    int count;
    Item *data;
    int capacity;
    // 需要注意的是一点对索引进行操作就一定要保证索引不要越界
    void shiftUp(int k)
    {
        while (k > 1 && data[k] > data[k / 2])
        {
            swap(data[k], data[k / 2]);
            k /= 2;
        }
    }
    void shiftDown(int k)
    {
        while (2 * k <= count)
        {
            int maxIdx = 2 * k;
            if (maxIdx + 1 <= count && data[maxIdx] < data[maxIdx + 1])
            {
                maxIdx += 1;
            }
            if (data[k] < data[maxIdx])
            {
                swap(data[k], data[maxIdx]);
                k = maxIdx;
            }
            else
            {
                break;
            }
        }
    }

    void heapify()
    {
        for (int i = count / 2; i > 0; i--)
        {
            shiftDown(i);
        }
    }

public:
    MaxHeap(int capacity)
    {
        data = new Item[capacity + 1];
        count = 0;
        this->capacity = capacity; //这种方式一般，最好的方式是可以自动的扩大堆
    }
    MaxHeap(Item arr[], int n)
    {
        data = new Item[n + 1];
        capacity = n;
        for (int i = 1; i <= n; i++)
        {
            data[i] = arr[i - 1];
        }
        count = n;
        heapify();
    }
    ~MaxHeap()
    {
        delete[] data;
    }
    int size()
    {
        return count;
    }
    int isEmpty()
    {
        return count == 0;
    }
    // 主要进行shiftup操作，所谓shiftup就是和父节点进行比较，对于最大堆来说，如果该节点比父节点的元素大，
    // 则和父节点交换位置
    void insert(Item item)
    {
        assert(count + 1 <= capacity);
        data[count + 1] = item;
        count++;
        shiftUp(count);
    }
    // TODO:实现testprint
    // shiftDown操作：取出堆顶元素，将堆尾元素放到堆顶，然后和子节点比较，一步步向下移动
    Item getMax()
    {
        assert(count > 0);
        Item ret = data[1];
        swap(data[count], data[1]);
        count--;
        shiftDown(1);
        return ret;
    }
};
#endif