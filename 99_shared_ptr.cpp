#include <iostream>
using namespace std;

template<typename T>
class SmartPtr {
public:
    SmartPtr(T* ptr);
    SmartPtr(const SmartPtr& obj);
    ~SmartPtr();

    SmartPtr<T>& operator=(const SmartPtr& obj);

    T& operator*();     // 返回若是T则会拷贝构造一个T, 此时*指针并不会改变其值
    T* operator->();

    int get_count();

private:
    T* ptr;
    int* count;
};

template<typename T>
SmartPtr<T>::SmartPtr(T* ptr) {
    this->ptr = ptr;
    this->count = new int(1);
    *(this->count) = 1;
}

template<typename T>
SmartPtr<T>::SmartPtr(const SmartPtr& obj) {
    this->ptr = obj.ptr;
    this->count = obj.count;
    ++(*obj.count);
}

template<typename T>
SmartPtr<T>::~SmartPtr() {
    if (--(*this->count) == 0) {
        delete this->ptr;   this->ptr = nullptr;
        delete this->count; this->count = nullptr;
    }
}

template<typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr& obj) {
    if (this != &obj) {
        delete this->ptr;   
        delete this->count; 
        this->ptr = obj.ptr;
        this->count = obj.count;
        (*obj.count)++;
    }
    return *this;
}

template<typename T>
T& SmartPtr<T>::operator*() {
    return *(this->ptr);
}
template<typename T>
T* SmartPtr<T>::operator->() {
    return this->ptr;
}
template<typename T>
int SmartPtr<T>::get_count() {
    return *(this->count);
}


class Test {
public:
    Test() { cout << "Test" << endl; }
    ~Test() { cout << "~Test" << endl; }
    int a = 0;
};

SmartPtr<Test> test() {
    SmartPtr<Test> p1(new Test);
    p1->a = 10;
    (*p1).a = 30;               // 用到左值的概念了, *operator如果返回T则是左值不能赋值, 改变, 寻址, T&就不一样了
    cout << p1.get_count() << endl;
    SmartPtr<Test> p2(p1);
    SmartPtr<Test> p3 = p1;

    cout << p1.get_count() << endl;
    cout << p2.get_count() << endl;
    cout << p3.get_count() << endl;

    SmartPtr<Test> p4(new Test);
    p4 = p2;
    cout << p4.get_count() << endl;

    return p4;
}

int main() {
    SmartPtr<Test> p = test();
    cout << p.get_count() << endl;
    cout << p->a << endl;
    cout << (*p).a << endl;     // 这里需加括号
    return 0;
}