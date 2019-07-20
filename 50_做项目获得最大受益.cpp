#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
    给定两个整数w和k, w代表拥有的初始资金, k代表最多可做k个项目. 
    再给定两个长度为N的正数数字cost[]和profits[], 代表一共有N个项目, cost[i]和profits[i]分别表示第i号项目的启动资金与做完后的利润
    (注意是利润, 如果一个项目启动资金为10, 利润为4, 代表该项目的最终收入为14). 
    一次只能做一个项目, 并且手里拥有自己大于或等于某个项目的启动资金时, 才能做这个项目. 
    该如何选择做项目, 可以使最终的受益最大
    说明： 每做完一个项目, 马上获得的收益, 可以支持你去做下
*/

class Node {
public:
    Node() { p = 0; c = 0; }
    int p;
    int c;
};

struct MinheapComparator {
    bool operator()(Node *a, Node *b) { return a->c > b->c; }
};

struct MaxheapComparator {
    bool operator()(Node *a, Node *b) { return a->c < b->c; }
};

int findMaximizedCapital(int k, int w, vector<int> &Profits, vector<int> &Capital) {
    Node *nodes = new Node[Profits.size()];
    for (int i = 0; i < Profits.size(); i++) {
        nodes[i].p = Profits[i];
        nodes[i].c = Capital[i];
    }
    priority_queue<Node*, vector<Node*>, MinheapComparator> minCostQ;
    priority_queue<Node*, vector<Node*>, MaxheapComparator> maxProfitQ;

    for (int i = 0; i < Profits.size(); i++) {
        minCostQ.push(&nodes[i]);
    }

    for (int i = 0; i < k; i++) {
        while ((!minCostQ.empty()) && (minCostQ.top()->c <= w)) {
            maxProfitQ.push(minCostQ.top());
            minCostQ.pop();
        }
        if (maxProfitQ.empty()) {
            return w;
        }
        w += maxProfitQ.top()->p;
        maxProfitQ.pop();
    }
    delete[] nodes;

    return w;
}

int main() {
    vector<int> cost = { 5, 10, 6, 20 };
    vector<int> prof = { 3, 2, 4, 9 };

    cout << findMaximizedCapital(4, 7, prof, cost) << endl;

    return 0;
}