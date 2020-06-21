#include <iostream>
using namespace std;

template<typename T>
void selectSort(T arr[],int n){
    for (int i = 0; i < n;i++){
        int minIdex = i;
        for (int j = i; j < n;j++){
            if(arr[j]<arr[minIdex])
                minIdex = j;
        }
        swap(arr[i], arr[minIdex]);
    }
}
int main(){
    cout << "hello world" << endl;
    return 0;
}