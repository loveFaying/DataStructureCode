#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;

template<typename T>
class MaxHeap{
private:
    T *data;
    int count;

public:
    // 构造函数, 构造一个空堆, 可容纳capacity个元素
    MaxHeap(int capacity){
        data = new T[capacity+1];
        count = 0;
    }

    ~MaxHeap(){
        delete[] data;
    }

    //返回堆中元素的个数
    int size(){
        return count;
    }

    //返回一个布尔值，表示堆中是否为空
    bool isEmpty(){
        return count == 0;
    }
};

int main(){

    MaxHeap<int> maxheap = MaxHeap<int>(100);
    cout << maxheap.size() << endl;
    cout << maxheap.isEmpty() << endl;

    return 0;
}