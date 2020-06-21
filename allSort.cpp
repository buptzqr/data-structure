#include <iostream>
#include <ctime>
#include <cassert>
using namespace std;

// 所有排序是从小到大排序

// 测试排序是否正确
template<class T>
bool sortTest(T arr[],int n){
    for (int i = 0; i < n-1; i++){
        if(arr[i]>arr[i+1])
            return false;
    }
    return true;
}

// 生成有n个元素的随机数组,每个元素的随机范围为[rangeL, rangeR]
int *generateRandomArray(int n, int rangeL, int rangeR) {

    assert(rangeL <= rangeR);

    int *arr = new int[n];

    srand(time(NULL));
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
    return arr;
}

// 每次选择最小的元素放在合适的位置
template<typename T>
void selectSort(T arr[],int n){
    for (int i = 0; i < n; i++){
        int minIdex = i;
        for (int j = i; j < n; j++){
            if(arr[j]<arr[minIdex])
                minIdex = j;
        }
        swap(arr[i], arr[minIdex]);
    }
}

// 前半部分是有序元素，后半部分是待排序部分，每次从后半部分取元素放在前半部分合适的位置
template<typename T>
void insertSort(T arr[],int n){
    for (int i = 1; i < n;i++){
        for (int j = i; j > 0;j--){
            if(arr[j]<arr[j-1])
                swap(arr[j], arr[j - 1]);
            else
                break;
        }
    }
}
// 插入排序的一种优化，因为插入排序使用了太多的swap，所以进行改进
// 改进方式就是将待排序的元素复制，将他和有序部分的元素比较，如果该元素比他大，则该元素向后移动一个位置
// 直到找到待排序元素的合适位置，将他填入
template<typename T>
void insertSort_v2(T arr[],int n){
    for (int i = 1;i< n; i++){
        T temp = arr[i];
        int j = i;//保存元素temp应该插入的位置
        for (; j > 0;j--){
            if(arr[j-1]>temp)
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
template<typename T>
void bubbleSort(T arr[], int n){
    for (int j = n - 1; j > 0; j--){
        for(int i = 0; i < j; i++){
            if(arr[i] > arr[i+1])
                swap(arr[i], arr[i + 1]);
            else
                break;
        }                
    }
}
// 冒泡排序改进版--待测试
template<typename T>
void bubbleSort_v2(T arr[],int n){
    for (int j = n - 1; j > 0; j--){
        T temp = arr[0];
        int i = 0;
        for(; i < j; i++){
            if(temp > arr[i + 1])
                arr[i] = arr[i + 1];
            else{
                arr[i] = temp;
                temp = arr[i + 1];
            }
        }
        arr[j] = temp;
    }
}

// 

int main(){
    
    cout << "hello world" << endl;
    return 0;
}