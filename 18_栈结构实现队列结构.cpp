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

class myQueue
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        int ret = stack2.top();
        stack2.pop();
        return ret;
    }

    int top() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        int ret = stack2.top();
        return ret;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
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
    cout << q.top() << endl;
    for (int i = 0; i < 5; i++)
        cout << q.pop() << " ";
    cout << endl;
    cout << q.top() << endl;


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