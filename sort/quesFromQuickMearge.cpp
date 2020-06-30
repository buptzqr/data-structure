#include <iostream>
#include <ctime>
using namespace std;
// reverse order pair逆序对
// 采用归并排序思路，归并的时候计算两个部分的逆序对数目
void mearge(int arr[], int l, int mid, int r, int &reversePairNum)
{
    int aux[r - l + 1];
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
            // reversePairNum += (r - mid); 错就错在这里i所指向的元素已经在下面被处理一次了，这里又处理了一次
        }
        else if (aux[i - l] <= aux[j - l])
        {
            arr[k] = aux[i - l];
            i++;
        }
        else
        {
            arr[k] = aux[j - l];
            // reversePairNum += (j - mid);
            reversePairNum += (mid - i + 1);
            j++;
        }
    }
}
void reverseCount(int arr[], int l, int r, int &reversePairNum)
{
    if (l >= r)
        return;
    int mid = (l + r) / 2;
    reverseCount(arr, l, mid, reversePairNum);
    reverseCount(arr, mid + 1, r, reversePairNum);
    mearge(arr, l, mid, r, reversePairNum);
}

// 求数组中的第n大的数，使用快速排序的思路
int partition(int arr[], int l, int r)
{
    srand(time(NULL));
    int selectElement = arr[rand() % l + (r - l + 1)];
    // [l+1,i]<element (j,r]>=element
    int i = l;
    int j = r;
    int k = l + 1;
    while (i < j)
    {
        if (arr[k] >= selectElement)
        {
            swap(arr[j], arr[k]);
            j--;
        }
        else
        {
            i++;
            k++;
        }
    }
    swap(arr[i], arr[l]);
    return i;
}
int findNFromM(int arr[], int l, int r, int n)
{
    if (l >= r)
    {
        return -1; //返回索引为-1代表没有找到
    }
    int k = partition(arr, l, r);
    if (k + 1 == n)
    {
        return k;
    }
    else if (k + 1 > n)
    {
        // 从左半边寻找
        findNFromM(arr, l, r - 1, n);
    }
    else
    {
        findNFromM(arr, l + 1, r, n);
    }
}
int main()
{
    int reverseArray[4] = {7, 5, 6, 4};
    int count = 0;
    reverseCount(reverseArray, 0, 3, count);
    cout << count;
    getchar();
}
