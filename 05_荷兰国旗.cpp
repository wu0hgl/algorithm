#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);

/*
    ����һ������arr, ��һ����num,
    ���С��num����������������, ����num��������������м�, ����num��������������ұ�
    Ҫ�����ռ临�Ӷ�O(1), ʱ�临�Ӷ�O(N)
*/

void func(vector<int> &arr, int left, int right, int aim) {
    int rightPtr = right + 1;   // ��ǰ��ָ��λ�þ��Ǵ���aim������߽�
    int leftPtr = left - 1;     // ��ǰ��ָ��λ�þ���С��aim�����ұ߽�
    int index = left;
    while (index < rightPtr) {  // ���ﲻ���е��ں�, ��ΪrightPtr��ָλ�þ��Ǵ���aim����߽�
        if (arr[index] < aim) 
            swap(arr[++leftPtr], arr[index++]);
        else if (arr[index] > aim) 
            swap(arr[index], arr[--rightPtr]);  // ���ұ߽罻�����������黹δ��aim�Ƚ�, ����index����
        else 
            index++;
        //printVector(arr);
    }
}

int main() {
    //vector<int> arr;
    //generatorRandomArray(arr, 30, 10);
    vector<int> arr = { 1, 4, 8 };
    printVector(arr);

    func(arr, 0, arr.size() - 1, 4);
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

    srand(static_cast<int>(time(NULL)));
    for (int i = 0; i < len; i++) {
        temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // �������������
        //temp = static_cast<int>(rand() % (maxValue + 1));                                         // �����������
        if (temp == 0) {
            continue;
        }
        else {
            vt.push_back(temp);
        }
    }
}