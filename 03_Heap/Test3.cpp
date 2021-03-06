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
    T *data;  // 从1号位置开始存储
    int count;
    int capacity;

    void shiftUp(int k){
        // 注意边界，要保证data[k/2]存在
        while(k > 1 && data[k/2] < data[k]){ 
            swap( data[k/2], data[k] );
            k /= 2;
        }
    }

    void shiftDown(int k){
        // 注意边界，表示k有孩子（至少有一个孩子是左孩子）
        while( 2*k <= count ){ 
            int j = 2*k; // 在此轮循环中,data[k]和data[j]交换位置
            if( j+1 <= count && data[j+1] > data[j] )
                j ++;
            // data[j] 是 data[2*k]和data[2*k+1]中的最大值

            if( data[k] >= data[j] ) break;
            swap( data[k] , data[j] );
            k = j;
        }
    }

public:
    // 构造函数, 构造一个空堆, 可容纳capacity个元素
    MaxHeap(int capacity){
        data = new T[capacity+1];
        count = 0;
        this->capacity = capacity;
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

    // 像最大堆中插入一个新的元素 item
    void insert(T item){
        assert( count + 1 <= capacity );
        data[count+1] = item;
        count ++;
        shiftUp(count);
    }

    // 顺序打印堆数组
    void printHeapData(){
        assert(count > 0);
        for(int i = 1 ; i <= count ; i ++)
            cout << data[i] << " ";
        cout << endl;
    }

    // 从最大堆中取出堆顶元素, 即堆中所存储的最大数据
    T extractMax(){
        assert( count > 0 );
        T ret = data[1];

        swap( data[1] , data[count] );
        count --;
        shiftDown(1);

        return ret;
    }

    // 获取最大堆中的堆顶元素
    T getMax(){
        assert( count > 0 );
        return data[1];
    }
};

int main(){

    MaxHeap<int> maxheap = MaxHeap<int>(100);
    
    int n = 20;   // 随机生成n个元素放入最大堆中
    srand(time(NULL));
    for(int i = 0 ; i < n ; i ++)
        maxheap.insert(rand()%100);
    
    int* arr = new int[n];

    for(int i = 0 ; i < n ; i ++){
        arr[i] = maxheap.extractMax();
        cout << arr[i] << " ";
    }
    cout << endl;

    // 确保arr数组是从大到小排列的
    for( int i = 1 ; i < n ; i ++ )
        assert( arr[i-1] >= arr[i] );
    
    delete[] arr;

    return 0;
}