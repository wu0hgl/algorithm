#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>
#include <queue>
#include <functional>
using namespace std;

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    栈结构实现队列
*/

class myQueue
{
public:
    myQueue() {
        stackPush = new stack<int>;
        stackPop = new stack<int>;
    }

    ~myQueue() {
        delete stackPush;
        delete stackPop;
    }

    void push(int node) {
        stackPush->push(node);
        cout << stackPush->size() << endl;
    }

    int pop() {
        if (stackPush->empty() && stackPop->empty()) {
            cout << "队列为空 pop err" << endl;
            return -1;
        }
        else if (stackPop->empty()){
            while (!stackPush->empty()) {
                stackPop->push(stackPush->top());
                stackPush->pop();
            }
        }
        int ret = stackPop->top();
        stackPop->pop();
        return ret;
    }

    int top() {
        if (stackPop->empty() && stackPush->empty()) {
            cout << "队列为空 top err" << endl;
            return -1;
        }
        else if (stackPop->empty()) {
            while (!stackPush->empty()) {
                stackPop->push(stackPush->top());
                stackPush->pop();
            }
        }

        int ret = stackPop->top();
        stackPop->pop();
        return ret;
    }

public:
    stack<int> *stackPush;
    stack<int> *stackPop;
};


int main() {
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 10, 10);
    printVector(arr);

    myQueue q;
    for (int i = 0; i < arr.size(); i++) {
        q.push(arr[i]);
        cout << q.top() << " ";
    }
    cout << endl;
    cout << q.stackPush->size() << endl;
    cout << "---------------" << endl;
    cout << q.top() << endl;
    cout << "---------------" << endl;
    for (int i = 0; i < 5; i++)
        cout << q.pop() << " ";
    cout << endl;
    cout << "---------------" << endl;
    cout << q.top() << endl;
    cout << "---------------" << endl;

    stack<int> sk;
    sk.push(2);
    sk.push(4);
    cout << sk.size() << endl;

    printVector(arr);

    return 0;
}

void printVector(vector<int> &vt) {
    for (auto v : vt)
        cout << v << " ";
    cout << endl;
}

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue) {
    int temp;
    int len = (int)(maxSize % (maxSize + 1));

    for (int i = 0; i < len; i++) {
        temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // 随机生成正负数
        //temp = static_cast<int>(rand() % (maxValue + 1));          // 随机生成正数
        vt.push_back(temp);
        //Insert_2(temp);
    }
}