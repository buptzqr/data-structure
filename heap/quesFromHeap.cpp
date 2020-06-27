#include <iostream>
using namespace std;
// 使用堆实现优先队列

// 使用堆在N个元素中取出前M个（指的是前M个大个元素），思路就是维护一个大小为M的最小堆，插入完成以后，前M个元素也就出来了

void shiftDown(int arr[], int i, int end)
{
    // int arrSize = sizeof(arr) / sizeof(arr[0]);
    while (2 * i <= end)
    {
        int minIdx = 2 * i;
        if (minIdx + 1 <= end && arr[minIdx + 1] < arr[minIdx])
            minIdx += 1;
        if (arr[i] < arr[minIdx])
            break;
        swap(arr[i], arr[minIdx]);
        i = minIdx;
    }
}
int *getTopM(int arr[], int n, int m)
{
    // 还是从1开始索引
    int *data = new int[m + 1];
    // 读入m-1个元素
    for (int i = 1; i < m; i++)
    {
        data[i] = arr[i - 1];
    }
    // heapify
    for (int i = (m - 1) / 2; i >= 0; i--)
    {
        shiftDown(data, i, m - 1);
    }
    //insert
    for (int i = m - 1; i <= n; i++)
    {
        data[m] = arr[i];
        // shiftup操作
        int j = m;
        while (j / 2 > 0 && data[2 / j] > data[j])
        {
            swap(data[j], data[2 / j]);
            j /= 2;
        }
        // getMax操作
        swap(arr[1], arr[m]);
    }
    return data;
}
// 多路归并排序：思路就是维护一个最小堆，每次从堆中取出最小的元素，然后再从最小元素所属的那部分数组中添加一个元素进堆

// TODO:最大最小堆
int main()
{
    int data = {};
}