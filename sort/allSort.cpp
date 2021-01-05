#include <iostream>
#include <ctime>
#include <cassert>
#include "../heap/heap.h"
#include <vector>
using namespace std;

// 所有排序是从小到大排序

// 测试排序是否正确
template <class T>
bool sortTest(T arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
            return false;
    }
    return true;
}

// 生成有n个元素的随机数组,每个元素的随机范围为[rangeL, rangeR]
int *generateRandomArray(int n, int rangeL, int rangeR)
{

    assert(rangeL <= rangeR);

    int *arr = new int[n];

    srand(time(NULL));
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
    return arr;
}

// 每次选择最小的元素放在合适的位置
template <typename T>
void selectSort(T arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int minIdex = i;
        for (int j = i; j < n; j++)
        {
            if (arr[j] < arr[minIdex])
                minIdex = j;
        }
        swap(arr[i], arr[minIdex]);
    }
}

// 前半部分是有序元素，后半部分是待排序部分，每次从后半部分取元素放在前半部分合适的位置
template <typename T>
void insertSort(T arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (arr[j] < arr[j - 1])
                swap(arr[j], arr[j - 1]);
            else
                break;
        }
    }
}
// 插入排序的一种优化，因为插入排序使用了太多的swap，所以进行改进
// 改进方式就是将待排序的元素复制，将他和有序部分的元素比较，如果该元素比他大，则该元素向后移动一个位置
// 直到找到待排序元素的合适位置，将他填入
template <typename T>
void insertSort_v2(T arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        T temp = arr[i];
        int j = i; //保存元素temp应该插入的位置
        for (; j > 0; j--)
        {
            if (arr[j - 1] > temp)
                arr[j] = arr[j - 1];
            else
                break;
        }
        arr[j] = temp;
    }
}
// 提前终止内层循环是插入排序非常重要的一个性质，如果数组基本有序插入排序的效率就会很高，因为内层循环终止的快
// 对于近乎有序的数组插入排序有时候要比nlog（n）的算法还要快，因为他会进化成一个O（n）级别的算法

// 冒泡排序
template <typename T>
void bubbleSort(T arr[], int n)
{
    for (int j = n - 1; j > 0; j--)
    {
        for (int i = 0; i < j; i++)
        {
            if (arr[i] > arr[i + 1])
                swap(arr[i], arr[i + 1]);
        }
    }
}
// 冒泡排序改进版--待测试
template <typename T>
void bubbleSort_v2(T arr[], int n)
{
    for (int j = n - 1; j > 0; j--)
    {
        T temp = arr[0];
        int i = 0;
        for (; i < j; i++)
        {
            if (temp > arr[i + 1])
                arr[i] = arr[i + 1];
            else
            {
                arr[i] = temp;
                temp = arr[i + 1];
            }
        }
        arr[j] = temp;
    }
}
// shell sort
template <typename T>
void shellSort(T arr[], int n)
{
    int k = n;
    vector<int> disVec;
    while (k >= 1)
    {
        disVec.push_back(k);
        k /= 3;
    }
    for (auto dis : disVec)
    {
        for (int i = 0; i < dis; i++)
        {
            for (int j = i + dis; j < n; j += dis)
            {
                for (int k = j; k >= i + dis; k -= dis)
                    if (arr[k] < arr[k - dis])
                        swap(arr[k], arr[k - dis]);
            }
        }
    }
}
/* 大神版本
template<typename T>
void shellSort(T arr[], int n){

    // 计算 increment sequence: 1, 4, 13, 40, 121, 364, 1093...
    int h = 1;
    while( h < n/3 )
        h = 3 * h + 1;

    while( h >= 1 ){

        // h-sort the array
        for( int i = h ; i < n ; i ++ ){

            // 对 arr[i], arr[i-h], arr[i-2*h], arr[i-3*h]... 使用插入排序
            T e = arr[i];
            int j;
            for( j = i ; j >= h && e < arr[j-h] ; j -= h )
                arr[j] = arr[j-h];
            arr[j] = e;
        }

        h /= 3;
    }
}
*/

// 归并排序：就是一个先不断切分，切到最底层，只有一个元素的时候，然后逐级向上归并
// 缺点就是额外多使用了o（n）的空间
// 凡是这种切分成和树一样的这种思路都要用到递归的思路
template <typename T>
void __mearge(T arr[], int l, int mid, int r)
{
    T aux[r - l + 1];
    for (int i = l; i <= r; i++)
    {
        aux[i - l] = arr[i];
    }
    int i = l;
    int j = mid + 1;
    for (int k = l; k <= r; k++)
    {
        if (i > mid)
        {
            arr[k] = aux[j - l];
            j++;
        }
        else if (j > r)
        {
            arr[k] = aux[i - l];
            i++;
        }
        else if (aux[i - l] < aux[j - l])
        {
            arr[k] = aux[i - l];
            i++;
        }
        else
        {
            arr[k] = aux[j - l];
            j++;
        }
    }
}
// 将[l,r]范围内的数据进行归并排序
template <typename T>
void __meargeSort(T arr[], int l, int r)
{
    if (l >= r)
        return;
    //改进二：对于所有的nlog（n）的算法可以在这里进行优化，即当n小到一定程度的话，使用插入排序的效率最高
    // if(r -l<=15){
    //     insertSort(arr, l, r);
    //     return;
    // }
    int mid = (l + r) / 2;
    __meargeSort(arr, l, mid);
    __meargeSort(arr, mid + 1, r);
    __mearge(arr, l, mid, r);
    //改进一：对是否进行__mearge操作进行判断
    // if (arr[mid] > arr[mid + 1])
    //     __mearge(arr, l, mid, r);
}

// 一种自底向上的排序方法，就是省略了分割过程，直接进行mearge操作
// 因为没有使用数组使用索引获取元素的性质，所以可以用这种方法对链表进行排序
template <typename T>
void __meargeSortBU(T arr[], int n)
{
    for (int sz = 1; sz <= n; sz += sz)
    {
        // 对[i,i+sz-1]和[i+sz,i+2*sz-1]进行归并
        for (int i = 0; i + sz < n; i += 2 * sz)
        {                                                             //i+sz小于n保证是两部分是存在的，否则归并没有意义
            __mearge(arr, i, i + sz - 1, min(n - 1, i + 2 * sz - 1)); //保证第二部分的右边没有越界
        }
    }
}

template <typename T>
void meargeSort(T arr[], int n)
{
    __meargeSort(arr, 0, n - 1);
}

// 快速排序:思路就是找一个元素，将元素放在合适的位置，这样元素左边都是比元素小的点，右边都是比元素大的点，如此再
//         对左右部分分别进行上述操作完成排序

template <typename T>
int partition(T arr[], int l, int r)
{
    // 优化二：因为快速排序每次选取的元素不一定位于整个数组的最中间，所以会导致分割的不均匀
    //        方法就是随机选取元素e,这个优化就是为了应对待排序数组近乎有序的情况
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    //[l+1,j]<e [j+1,i)>e
    T e = arr[l];
    int j = l;
    for (int i = l + 1; i <= r; i++)
    {
        if (arr[i] < e)
        {
            swap(arr[j + 1], arr[i]);
            j++;
        }
    }
    swap(arr[l], arr[j]);
    return j;
}

template <typename T>
int partition_v2(T arr[], int l, int r)
{
    // 优化三：这个优化是为了避免有大量的重复元素造成的分布不均匀，因为我们的分割分成的
    // 左半部分是<e的，右半部分是>=e的，大量的重复元素可能集中在右半部分
    // 具体思路图示见云笔记
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    // [l+1,i)<=e (j,r]>=e
    T e = arr[l];
    int i = l + 1;
    int j = r;
    while (true)
    {
        while (i <= r && arr[i] < e)
            i++;
        while (j >= l + 1 && arr[j] > e)
            j--;
        if (i > j)
            break;
        else
        {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    swap(arr[l], arr[j]);
    return j;
}

template <typename T>
void __quickSort(T arr[], int l, int r)
{
    if (l >= r)
    {
        return;
    }
    // 优化一：到底层的时候可以使用插入排序
    // if(r-l>=15){
    //     insertSort(arr, l, r);
    //     return;
    // }
    int j = partition_v2(arr, l, r);
    __quickSort(arr, l, j - 1);
    __quickSort(arr, j + 1, r);
}

// 三路快排，也是为了处理有大量重复元素的情况
// 思路就是将整个数组分成了三部分，<e =e 和>e
template <typename T>
void __threeWayQuickSort(T arr[], int l, int r)
{
    //[l+1,lt]<e [gt,r]>e [lt+1,i)=e
    if (l >= r)
        return;
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    int lt = l;
    int gt = r + 1;
    int i = l + 1;
    T e = arr[l];
    while (i < gt)
    {
        if (arr[i] < e)
        {
            swap(arr[i], arr[lt + 1]);
            lt++;
            i++;
        }
        else if (arr[i] > e)
        {
            swap(arr[i], arr[gt - 1]);
            gt--;
        }
        else
        {
            i++;
        }
    }
    swap(arr[l], arr[lt]);
    __threeWayQuickSort(arr, l, lt - 1);
    __threeWayQuickSort(arr, gt, r);
}

template <typename T>
void quickSort(T arr[], int n)
{
    srand(time(NULL));
    // __quickSort(arr, 0, n - 1);
    __threeWayQuickSort(arr, 0, n - 1);
}

template <typename T>
void heapSort(T arr[], int n)
{
    MaxHeap<T> maxHeap = MaxHeap<T>(n);
    for (int i = 0; i < n; i++)
    {
        maxHeap.insert(arr[i]);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        arr[i] = maxHeap.getMax();
    }
}

// 使用了heapify操作来建堆，heapify操作的建堆过程是一个o（n）的过程
template <typename T>
void heapSort_v2(T arr[], int n)
{
    MaxHeap<T> maxHeap = MaxHeap<T>(arr, n);
    for (int i = n - 1; i >= 0; i--)
    {
        arr[i] = maxHeap.getMax();
    }
}

// 原地堆排序：就是说先进行heapify操作得到最大堆，然后将堆顶元素和堆尾元素交换，再对堆顶元素进行shiftdown操作，
// 如此往复即可,此处堆是从0索引开始的
template <typename T>
void __shiftDown(T arr[], int n, int i)
{
    while (2 * i + 1 < n)
    {
        int maxIdx = 2 * i + 1;
        if (maxIdx + 1 < n && arr[maxIdx + 1] > arr[maxIdx])
            maxIdx += 1;
        if (arr[i] > arr[maxIdx])
            break;
        swap(arr[i], arr[maxIdx]);
        i = maxIdx;
    }
}

template <typename T>
void heapSort_v3(T arr[], int n)
{
    // heapify
    for (int i = (n - 1) / 2; i >= 0; i--)
        __shiftDown(arr, n, i);
    // 移动操作,i就是最后当前要和第一个元素交换的位置
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        __shiftDown(arr, i, 0);
    }
}

int main()
{
    int *arr = generateRandomArray(100, 0, 1000);
    shellSort(arr, 100);
    if (sortTest(arr, 100))
    {
        cout << "sort right" << endl;
        return 0;
    }
    cout << "sort wrong" << endl;
    delete[] arr;
    return 0;
}