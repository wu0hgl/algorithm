#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>
#include <queue>
#include <functional>
using namespace std;

void generatorRandomArray(vector<int> &vt, int maxValueSize, int minValue);
void printVector(vector<int> &vt);

/*
    如何可以得到数据流中排序后的中位数
*/

priority_queue<int, vector<int>, less<int>> p;      // 降序, 最大堆, 最大堆
priority_queue<int, vector<int>, greater<int>> q;   // 升序, 最小堆, 最小堆


void Insert_1(int num){
    if (p.empty() || num <= p.top()) 
        p.push(num);
    else 
        q.push(num);
    if (p.size() == q.size() + 2) { 
        q.push(p.top());
        p.pop();
    }
    if (p.size() + 1 == q.size()) { 
        p.push(q.top());
        q.pop();
    }
}
double GetMedian_1(){
    return p.size() == q.size() ? (p.top() + q.top()) / 2.0 : p.top();
}

vector<int> minValue;
vector<int> maxValue;
void Insert_2(int num)
{
    if (((minValue.size() + maxValue.size()) & 1) == 0) {    // 偶数, 应该插入最小堆中
        if (maxValue.size() > 0 && maxValue[0] > num) {    // 最大堆中的数字大于要插入的数字
            maxValue.push_back(num);
            push_heap(maxValue.begin(), maxValue.end(), less<int>());

            num = maxValue[0];

            pop_heap(maxValue.begin(), maxValue.end(), less<int>());
            maxValue.pop_back();
        }
        minValue.push_back(num);
        push_heap(minValue.begin(), minValue.end(), greater<int>());
    }
    else {        // 奇数, 插入最大堆
        if (minValue.size() > 0 && minValue[0] < num) {   // 最小堆小于这个数
            minValue.push_back(num);
            push_heap(minValue.begin(), minValue.end(), greater<int>());

            num = minValue[0];

            pop_heap(minValue.begin(), minValue.end(), greater<int>());
            minValue.pop_back();
        }
        maxValue.push_back(num);
        push_heap(maxValue.begin(), maxValue.end(), less<int>());
    }
}
double GetMedian_2()
{
    int size = minValue.size() + maxValue.size();

    if (0 == size)
        return 0;

    if ((size & 1) == 1)
        return minValue[0];
    else
        return (minValue[0] + maxValue[0]) / 2.0;
}

double getMedian(vector<int> vt) {
    if ((vt.size() % 2) == 0)
        return (vt[vt.size() / 2] + vt[vt.size() / 2 - 1]) / 2.0;
    else
        return vt[vt.size() / 2];
}

int main() {
    vector<int> arr;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 5, 10);
    printVector(arr);

    cout << GetMedian_1() << endl;
    cout << GetMedian_2() << endl;

    sort(arr.begin(), arr.end());
    cout << getMedian(arr) << endl;
    printVector(arr);

    return 0;
}

void printVector(vector<int> &vt) {
    for (auto v : vt)
        cout << v << " ";
    cout << endl;
}

void generatorRandomArray(vector<int> &vt, int maxValueSize, int minValue) {
    int temp;
    int len = (int)(maxValueSize % (maxValueSize + 1));

    for (int i = 0; i < len; i++) {
        temp = static_cast<int>(rand() % (minValue + 1)) - static_cast<int>(rand() % (minValue));   // 随机生成正负数
        //temp = static_cast<int>(rand() % (minValue + 1));          // 随机生成正数
        vt.push_back(temp);
        Insert_2(temp);
        Insert_1(temp);
    }
}
