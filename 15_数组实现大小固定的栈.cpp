#include <iostream>
using namespace std;

/*
    ������ṹʵ�ִ�С�̶�ջ
*/

class ArrayToStack{
public:
    ArrayToStack(int size) {
        m_p = (int *)malloc(sizeof(int) * size);
        m_maxSize = size;
        m_currentSize = 0;
    }
    int peek() {
        if (m_currentSize == 0) {
            cout << "���鳤��Ϊ0" << endl;
            return -1;
        }
        return m_p[m_currentSize - 1];
    }
    int push(int data) {
        if (m_currentSize == m_maxSize) {
            cout << "��������" << endl;
            return 0;
        }
        m_p[m_currentSize] = data;
        m_currentSize++;
    }
    int pop() {
        int ret = 0;
        if (m_currentSize == 0) {
            cout << "�����ѿ�" << endl;
            return ret;
        }
            ret = m_p[m_currentSize - 1];
            m_currentSize--;
            return ret;
    }
    ~ArrayToStack() {
        if (m_p != nullptr) {
            free(m_p);
            m_p = nullptr;
        }
        m_currentSize = 0;
        m_maxSize = 0;
    }
private:
    int m_maxSize;
    int m_currentSize;
    int *m_p;
};

void test() {
    ArrayToStack as(10);
    for (int i = 0; i < 10; i++) {
        //cout << as.peek() << endl;
        as.push(i + 1);
        cout << as.peek() << endl;
    }

    cout << "---------" << endl;

    for (int i = 0; i < 11; i++) {
        cout << as.peek() << endl;
        cout << as.pop() << endl;
    }
}

int main() {
    test();

    return 0;
}