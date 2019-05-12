#include <iostream>
using namespace std;

/*
    用数组结构实现大小固定队列
*/

class ArrayToQueue{
public:
    ArrayToQueue(int size) {
        m_p = (int *)malloc(size * sizeof(int));
        m_arraySize = size;
        m_start = 0;
        m_end = 0;
        m_size = 0;
    }

    int peek() {
        if (m_size == 0) {
            cout << "队列为空" << endl;
            return -1;
        }

        return m_p[m_start];
    }

    void push(int data) {
        if (m_size == m_arraySize) {
            cout << "队列已满" << endl;
            return;
        }
        m_size++;
        m_p[m_end] = data;
        m_end = (m_end == m_arraySize - 1) ? 0 : m_end + 1;
    }

    int poll() {
        if (m_size == 0) {
            cout << "队列为空" << endl;
            return -1;
        }
        m_size--;
        int temp = m_start;
        m_start = (m_start == m_arraySize - 1) ? 0 : m_start + 1;
        return m_p[temp];
    }

    ~ArrayToQueue() {
        if (m_p != nullptr) {
            free(m_p);
            m_p = nullptr;
        }
        m_arraySize = 0;
        m_start = 0;
        m_end = 0;
        m_size = 0;
    }
private:
    int *m_p;
    int m_arraySize;
    int m_start;
    int m_end;
    int m_size;
};

void test() {
    ArrayToQueue aq(10);
    for (int i = 0; i < 10; i++) {
        aq.push(i + 1);
        cout << aq.peek() << endl;
    }
    cout << "----------" << endl;
    aq.push(11);
    cout << "----------" << endl;
    for (int i = 0; i < 5; i++) {
        cout << aq.poll() << endl;
    }
    cout << "----------" << endl;
    cout << aq.peek() << endl;
}

int main() {
    test();

    return 0;
}