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
    for (int k = l; k < r; k++)
    {
        if (i > mid)
        {
            arr[k] = aux[j];
            j++;
        }
        else if (j > r)
        {
            arr[k] = aux[j];
            i++;
        }
        else if (aux[i] < aux[j])
        {
            arr[k] = aux[i];
            i++;
        }
        else
        {
            arr[k] = aux[j];
            j++;
        }
    }
}

// 求数组中的第n大的数，使用快速排序的思路
