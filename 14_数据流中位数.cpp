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
    ��ο��Եõ�����������������λ��
*/

priority_queue<int, vector<int>, less<int>> p;      // ����, ����, ����
priority_queue<int, vector<int>, greater<int>> q;   // ����, ��С��, ��С��


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

/*
vector<int> min;
vector<int> max;

void Insert_2(int num)
{
    if (((min.size() + max.size()) & 1) == 0) {    // ż��, Ӧ�ò�����С����
        if (max.size() > 0 && max[0] > num) {    // �����е����ִ���Ҫ���������
            max.push_back(num);
            push_heap(max.begin(), max.end(), less<int>());

            num = max[0];

            pop_heap(max.begin(), max.end(), less<int>());
            max.pop_back();
        }
        min.push_back(num);
        push_heap(min.begin(), min.end(), greater<int>());
    }
    else {        // ����, ��������
        if (min.size() > 0 && min[0] < num) {   // ��С��С�������
            min.push_back(num);
            push_heap(min.begin(), min.end(), greater<int>());

            num = min[0];

            pop_heap(min.begin(), min.end(), greater<int>());
            min.pop_back();
        }
        max.push_back(num);
        push_heap(max.begin(), max.end(), less<int>());
    }
}

double GetMedian_2()
{
    int size = min.size() + max.size();

    if (0 == size)
        return 0;

    if ((size & 1) == 1)
        return min[0];
    else
        return (min[0] + max[0]) / 2.0;
}
*/

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
    //cout << GetMedian_2() << endl;
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

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue) {
    int temp;
    int len = (int)(maxSize % (maxSize + 1));

    for (int i = 0; i < len; i++) {
        temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // �������������
        //temp = static_cast<int>(rand() % (maxValue + 1));          // �����������
        vt.push_back(temp);
        Insert_1(temp);
        //Insert_2(temp);
    }
}
