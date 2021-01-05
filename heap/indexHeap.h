// 原本构建heap要交换大量的元素，这种交换的性能损耗比较大
// 元素位置发生改变，导致无法进行索引
// 索引堆构建堆的元素是索引
// data的存储位置没有发生改变
// 元素比较的时候比的是data，元素交换的时候，交换的是索引
// 一个关键点就是记住indexes的内容是元素的索引，indexes的索引是元素在堆中的位置
// reverse表示索引i在堆中的位置 也就是index[j] = i reverse[i] = j indexes[reverse[i]]=i reverse[indexes[i]]=i
// reverse这个技术叫反向查找技术(就是索引和值互相调换了一下)
#ifndef INDEX_HEAP
#define INDEX_HEAP
#include <iostream>
#include <cassert>
template <typename Item>
class IndexMaxHeap
{
private:
    int count;
    int *indexes;
    int *reverse;
    Item *data;
    int capacity;
    // 需要注意的是一旦对索引进行操作就一定要保证索引不要越界
    void shiftUp(int k)
    {
        while (k > 1 && data[indexes[k]] > data[indexes[k / 2]])
        {
            swap(indexes[k], indexes[k / 2]);
            reverse[indexes[k / 2]] = k / 2;
            reverse[indexes[k]] = k;
            k /= 2;
        }
    }
    void shiftDown(int k)
    {
        while (2 * k <= count)
        {
            int maxIdx = 2 * k;
            if (maxIdx + 1 <= count && data[indexes[maxIdx]] < data[indexes[maxIdx + 1]])
            {
                maxIdx += 1;
            }
            if (data[indexes[k]] < data[indexes[maxIdx]])
            {
                swap(indexes[k], indexes[maxIdx]);
                reverse[indexes[k]] = k;
                reverse[indexes[maxIdx]] = maxIdx;
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
    IndexMaxHeap(int capacity)
    {
        data = new Item[capacity + 1];
        indexes = new int[capacity + 1];
        reverse = new int[capacity + 1];
        for (int i = 1; i <= capacity; i++)
            reverse[i] = 0;
        count = 0;
        this->capacity = capacity; //这种方式一般，最好的方式是可以自动的扩大堆
    }

    ~IndexMaxHeap()
    {
        delete[] data;
        delete[] indexes;
        delete[] reverse;
    }
    int size()
    {
        return count;
    }
    int isEmpty()
    {
        return count == 0;
    }
    // 对于用户来说是从0开始索引的
    void insert(int i, Item item)
    {
        assert(count + 1 <= capacity);
        assert(i + 1 > 0 && i + 1 <= capacity);
        i += 1;
        data[i] = item;
        indexes[count + 1] = i;
        reverse[i] = count + 1;
        count++;
        shiftUp(count);
    }
    // TODO:实现testprint
    // shiftDown操作：取出堆顶元素，将堆尾元素放到堆顶，然后和子节点比较，一步步向下移动
    Item getMax()
    {
        assert(count > 0);
        Item ret = data[indexes[1]];
        swap(indexes[count], indexes[1]);
        reverse[indexes[1]] = 1;
        reverse[indexes[count]] = 0;
        count--;
        shiftDown(1);
        return ret;
    }
    int getMaxIndex()
    {
        assert(count > 0);
        int ret = indexes[1] - 1;
        return ret;
    }
    // 索引为i的元素是否在堆中
    bool contain(i)
    {
        // 也不一定要这样做，直接用count来做不就行了？因为getMax其实导致堆失效了
        assert(i + 1 >= 1 && i + 1 <= capacity);
        return reverse[i + 1] != 0;
    }

    Item getItem(int i)
    {
        assert(contain(i));
        return data[i + 1];
    }

    // 此时时间复杂度是o（n），这个操作就是要随便改变一个位置的元素的值，然后再重新构建堆，reverse的好处也就是在这里了
    void change(int i, Item item)
    {
        assert(contain(i));
        i += 1;
        data[i] = item;
        // 找到indexes[j] = i,j表示data在堆中的位置
        // 之后shiftdown和shiftup
        for (int j = 1; j <= count; j++)
        {
            if (indexes[j] == i)
            {
                shiftDown(j);
                shiftUp(j);
                return;
            }
        }
    }

    void change_v2(int i, Item item)
    {
        i += 1;
        data[i] = item;
        shiftDown(reverse[i]);
        shiftUp(reverse[i]);
    }
};
#endif