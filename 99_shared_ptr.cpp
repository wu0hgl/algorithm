#include <iostream>
using namespace std;

template<typename T>
class SmartPtr {
public:
    SmartPtr(T* ptr);
    SmartPtr(const SmartPtr& obj);
    ~SmartPtr();

    SmartPtr<T>& operator=(const SmartPtr& obj);

    T operator*();
    T* operator->();

    int get_count();

private:
    T* ptr;
    int* count;
};

template<typename T>
SmartPtr<T>::SmartPtr(T* ptr) {
    this->ptr = ptr;
    count = new int(1);
    *count = 1;
}

template<typename T>
SmartPtr<T>::SmartPtr(const SmartPtr& obj) {
    this->ptr = obj.ptr;
    this->count = obj.count;
    ++(*this->count);
}

template<typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr& obj) {
    if (this != &obj) {
        ++(*obj.count);
        if (--(*this->count) == 0) {
            delete this->ptr;   this->ptr = nullptr;
            delete this->count; this->count = nullptr;
        }
        this->ptr = obj.ptr;
        this->count = obj.count;
    }
    return *this;
}


template<typename T>
SmartPtr<T>::~SmartPtr() {
    if (--(*this->count) == 0) {
        delete this->ptr;   this->ptr = nullptr;
        delete this->count; this->count = nullptr;
    }
}

template<typename T>
T SmartPtr<T>::operator*() {
    return *this->ptr;
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
    return 0;
}