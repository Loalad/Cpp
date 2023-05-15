#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

template <class T, size_t kSize = 10>
class Queue {
    template<class U, size_t size>
    friend std::ostream &operator<<(std::ostream &os, const Queue<U, size> &q);
//        for(int i = q._front; i <= q._rear; ++i) {
//            os << q._data[i] << " ";
//        }
//        return os;
//    }
public:
    Queue():_front(0), _rear(0), _data(new T[kSize]()) {
        cout << "Queue()" << endl;
    }
    bool full() const;
    bool empty() const;
    void push(const T &value);
    void pop();
    T front();
    T rear();
    ~Queue();
private:
    int _front;
    int _rear;
    T *_data;
};

template<class T, size_t kSize>
bool Queue<T, kSize>::full() const {
    return (_front == (_rear + 1) % kSize);
}

template<class T, size_t kSize>
bool Queue<T, kSize>::empty() const {
    return  _front == _rear;
}

template<class T, size_t kSize>
void Queue<T, kSize>::push(const T &value) {
    if(!full()){
        _data[_rear++] = value;
        _rear %= kSize;
    }else {
        cout << "The queue is full" << endl;
        return;
    }
}

template<class T, size_t kSize>
void Queue<T, kSize>::pop() {
    if(!empty()) {
        ++_front;
        _front %= kSize;
    }else {
        cout << "The queue is empty" << endl;
        return;
    }
}

template<class T, size_t kSize>
T Queue<T, kSize>::front() {
    return _data[_front];
}

template<class T, size_t kSize>
T Queue<T, kSize>::rear() {
    return _data[(_rear - 1 + kSize) % kSize];
}

template<class T, size_t kSize>
Queue<T, kSize>::~Queue() {
    cout << "~Queue()" << endl;
    if(_data) {
        delete []_data;
        _data = nullptr;
    }
}

template<class T, size_t kSize>
std::ostream &operator<<(std::ostream &os, const Queue<T, kSize> &q) {
    for(int i = q._front; i <= q._rear; ++i) {
        os << q._data[i] << " ";
    }
    return os;
}

void test() {
    Queue<int> queue;
    cout << "队列是否为空:" << queue.empty() << endl;

    queue.push(1);
    cout << "队列的尾为：" << queue.rear() << endl;

    cout << "队列是否为空:" << queue.empty() << endl;

    cout << "队列的头为：" << queue.front() << endl;

    for(int i = 2; i < 12; ++i) {
        queue.push(i);
        cout << queue << endl;
    }
    cout << queue << endl;
    cout << "队列的尾为：" << queue.rear() << endl;

    for(int i = 0; i < 5; ++i) {
        queue.pop();
        cout << queue << endl;
    }
}

int main()
{
    test();
    return 0;
}

