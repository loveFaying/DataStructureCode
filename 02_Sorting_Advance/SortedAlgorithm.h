#ifndef SORTED_ALGORITHM_H_1
#define SORTED_ALGORITHM_H_1

#include <iostream>
#include <cassert>
#include <ctime>
#include <algorithm>

namespace SortedAlgorithm{

// 将arr[l...mid] 和 arr[mid+1...r] 两部分继续排序
template<typename T>
void __merge(T arr[], int l, int mid, int r){

    T* aux = new T[r-l+1];  // 新开辟一个辅助数组aux, 数组大小为r-l+1

    for(int i = l ; i <= r ; i ++ )
        aux[i-l] = arr[i];
    
    // 初始化，i指向左半部分的起始索引位置l；j指向右半部分起始索引位置mid+1
    // k指向原数组arr
    int i = l, j = mid+1;
    for(int k = l ; k <= r ; k ++){
        
        if(i > mid){ // 如果左半部分元素已经全部处理完毕
            arr[k] = aux[j-l]; j ++;
        }else if(j > r){  // 如果右半部分元素已经全部处理完毕
            arr[k] = aux[i-l]; i ++;
        }else if(aux[i-l] < aux[j-l]){
            arr[k] = aux[i-l]; i ++;  // 左半部分所指元素 < 右半部分所指元素
        }else{  // 左半部分所指元素 >= 右半部分所指元素
            arr[k] = aux[j-l]; j ++;
        }
    }

    delete[] aux; // 别忘了回收aux
}

// 递归使用归并排序，对arr[l...r]范围进行排序
template<typename T>
void __mergeSort1(T arr[], int l, int r){

    if(l >= r)
        return;

    int mid = (l+r)/2;
    __mergeSort1(arr, l, mid);
    __mergeSort1(arr, mid+1, r);
    __merge(arr, l, mid, r);
}

template<typename T>
void mergeSort1(T arr[], int n){

    __mergeSort1(arr, 0, n-1);
}    

// 对arr[l...r]范围的数组进行插入排序
template<typename T>
void insertionSort(T arr[], int l, int r){

    for( int i = l+1 ; i <= r ; i ++ ) {

        T e = arr[i];
        int j;
        for (j = i; j > l && arr[j-1] > e; j--)
            arr[j] = arr[j-1];
        arr[j] = e;
    }

    return;
}

// 使用优化的归并排序算法, 对arr[l...r]的范围进行排序
template<typename T>
void __mergeSort2(T arr[], int l, int r){

    // 优化2: 对于小规模数组, 使用插入排序
    if( r - l <= 15 ){
        insertionSort(arr, l, r);
        return;
    }

    int mid = (l+r)/2;
    __mergeSort2(arr, l, mid);
    __mergeSort2(arr, mid+1, r);

    // 优化1: 对于arr[mid] <= arr[mid+1]的情况,不进行merge
    // 对于近乎有序的数组非常有效,但是对于一般情况,有一定的性能损失
    if( arr[mid] > arr[mid+1] )
        __merge(arr, l, mid, r);
}

template<typename T>
void mergeSort2(T arr[], int n){

    __mergeSort2(arr, 0, n-1);
}

// 自底向上的使用归并排序算法
template<typename T>
void mergeSortBU1(T arr[], int n){

    // 无优化版本
    for(int sz = 1 ; sz < n ; sz += sz){
        for(int i = 0 ; i < n-sz ; i += sz+sz){
           // 对 arr[i...i+sz-1] 和 arr[i+sz...i+2*sz-1] 进行归并
            __merge(arr, i, i+sz-1, std::min(i+sz+sz-1, n-1));
        }
    }
}

template<typename T>
void mergeSortBU2(T arr[], int n){

    // 优化版本
    // 对于小数组，使用插入排序优化
    for(int i = 0 ; i < n ; i += 16){
        insertionSort(arr, i, std::min(i+15, n-1));
    }

    for(int sz = 16 ; sz < n ; sz += sz){
        for(int i = 0 ; i < n-sz ; i += sz+sz){

            // 对于arr[mid] <= arr[mid+1]的情况,不进行merge
            if( arr[i+sz-1] > arr[i+sz] )
                __merge(arr, i, i+sz-1, std::min(i+sz+sz-1,n-1) );
        }
    }
}
};

#endif