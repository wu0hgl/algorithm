#include <iostream>
#include <queue>
using namespace std;

/*
    仅用队列结构实现栈
*/

class MyStack {
public:
    MyStack() {
        m_queue = new queue<int>;
        m_help = new queue<int>;
    }
    int peek() {
        if (m_queue->empty() && m_help->empty()) {
            cout << "队列空 peek err" << endl;
            return -1;
        }
        while (m_queue->size() != 1) {
            m_help->push(m_queue->front());
            m_queue->pop();
        }
        int res = m_queue->front();
        m_help->push(res);
        m_queue->pop();
        swap();
        return res;
    }

    void swap() {
        queue<int> *temp = m_help;
        m_help = m_queue;
        m_queue = temp;
    }

    int pop() {
        if (m_queue->empty() && m_help->empty()) {
            cout << "队列空 peek err" << endl;
            return -1;
        }
        while (m_queue->size() > 1) {
            m_help->push(m_queue->front());
            m_queue->pop();
        }
        int res = m_queue->front();
        //m_help->push(res);
        m_queue->pop();
        swap();
        return res;
    }

    void push(int data) {
        m_queue->push(data);
    }

private:
    queue<int> *m_queue;
    queue<int> *m_help;
};

void test() {
    MyStack sk;
    for (int i = 0; i < 10; i++) {
        sk.push(i + 1);
        cout << sk.peek() << " ";
    }
    cout << endl;
    cout << "======================" << endl;
    for (int i = 0; i < 10; i++) {
        cout << sk.peek() << " ";
        sk.pop();
    }
    cout << endl;
}

int main() {

    test();
    return 0;
}