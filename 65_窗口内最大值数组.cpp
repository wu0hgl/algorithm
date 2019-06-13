#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    ����arr��һ����СΪw�Ĵ��ڴ����������߻������ұ�, ����ÿ�����һ�һ��λ��.
    ������鳤��Ϊn, ���ڴ�СΪw, ��һ������n-w+1�����ڵ����ֵ.
    ʵ��һ������:
        ����: ��������arr, ���ڴ�СΪw
        ���: һ������Ϊn-w+1������res, res[i]��ʾÿһ�ִ���״̬�µ�
*/

vector<int> getMaxWindow_1(vector<int> arr, int w) {
    vector<int> res;
    int len = static_cast<int>(arr.size());
    if ((len == 0) || (w < 1) || (len < w)) {
        return res;
    }

    res.resize(len - w + 1);
    deque<int> qmax;
    int index = 0;
    for (int i = 0; i < len; i++) {
        while ((!qmax.empty()) && (arr[qmax.back()] <= arr[i])) {
            qmax.pop_back();
        }
        qmax.push_back(i);
        if (qmax.front() == i - w) {    // ��ʼʱ�±�û�γ���ȫ, �������κ�Ԫ�ص���
            qmax.pop_front();
        }
        if (i >= w - 1) {
            res[index++] = arr[qmax.front()];
        }
    }

    return res;
}

vector<int> getMaxWindow_2(vector<int> arr, int w) {
    vector<int> res;
    int len = static_cast<int>(arr.size());
    if ((len == 0) || (w < 1) || (len < w)) {
        return res;
    }

    int outer;
    int inner;
    for (outer = 0; outer < len - w + 1; outer++) {
        int maxValue = INT_MIN;
        for (inner = outer; inner < outer + w; inner++) {
            if (arr[inner] > maxValue) {
                maxValue = arr[inner];
            }
        }
        res.push_back(maxValue);
    }

    return res;
}

int main() {
    vector<int> arr;
    vector<int> res;
    srand(static_cast<int>(time(NULL)));
    generatorRandomArray(arr, 10, 10);
    //vector<int> arr = { 4, 3, 5, 4, 3, 3, 6, 7 };
    printVector(arr);

    res = getMaxWindow_1(arr, 3);
    printVector(res);

    res = getMaxWindow_2(arr, 3);
    printVector(res);

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
        //temp = static_cast<int>(rand() % (range + 1));          // �����������
        vt.push_back(temp);
    }
}