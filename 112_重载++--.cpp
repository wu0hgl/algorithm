#include<iostream>
using namespace std;
class Test {
    friend Test& operator--(Test &obj);
    friend Test operator--(Test &obj, int);
public:
    Test(int a = 0, int b = 0) {
        this->a = a;
        this->b = b;
    }
    void display() {
        cout << "a:" << a << " b:" << b << endl;
    }
public:
    Test & operator++() {   // 前置++
        this->a++;
        this->b++;
        return *this;
    }
    Test operator++(int) {  // 后置++
        Test temp = *this;
        this->a++;
        this->b++;
        return temp;
    }
private:
    int a;
    int b;
};

Test& operator--(Test &obj) {      // 前置--
    obj.a--;
    obj.b--;
    return obj;
}

Test operator--(Test &obj, int) {   //后置--
    Test temp = obj;
    obj.a--;
    obj.b--;
    return temp;
}

int main() {
    Test t1(1, 2);
    t1.display();
    ++t1;
    t1.display();
    --t1;
    t1.display();
    Test t2(3, 4);
    t2.display();
    t2++;
    t2.display();
    t2--;
    t2.display();

    return 0;
}