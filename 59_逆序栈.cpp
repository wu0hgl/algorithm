#include <iostream>
#include <stack>
using namespace std;

/*
    逆序栈, 不能申请额外的数据结构, 只能使用递归函数
*/

int getAndRemoveLastElement(stack<int> &sk) {
    int res = sk.top();
    sk.pop();
    if (sk.empty()) {       // 获得最后一个元素没有压入栈
        return res;
    }
    else {
        int last = getAndRemoveLastElement(sk);
        sk.push(res);       // 恢复栈
        return last;
    }
}

void reverseStack(stack<int> &sk) {
    if (sk.empty()) {
        return ;
    }
    int i = getAndRemoveLastElement(sk);    // 获得最后一个元素
    reverseStack(sk);
    sk.push(i);
}

int main() {
    stack<int> sk;
    for (int i = 0; i < 10; i++)
        sk.push(i + 1);
    
    reverseStack(sk);

    while (!sk.empty()) {
        cout << sk.top() << " ";
        sk.pop();
    }
    cout << endl;

    return 0;
}