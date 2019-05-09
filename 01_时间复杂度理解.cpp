#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

/*
    һ����������A, ��һ����������B, ��ӡB�����в���A�е�����, A���鳤��ΪN, B���鳤��ΪM
*/

void printV(vector<int> &vt) {
    for (auto v : vt)
        cout << v << " ";
    cout << endl;
}

// ������
void func_1(vector<int> &a, vector<int> &b) {
    size_t out, in;
    for (out = 0; out < b.size(); out++) {
        for (in = 0; in < a.size(); in++) {
            if (b[out] == a[in])
                break;
        }
        if (in == a.size())
            cout << b[out] << " ";
    }
    cout << endl;
}

bool find(vector<int> &arr, int target) {
    int mid = 0;
    int start = 0;
    int end = arr.size() - 1;
    while (start <= end) {
        mid = start + ((end - start) >> 1);
        if (arr[mid] == target)
            return true;
        else {
            if (arr[mid] > target)
                end = mid - 1;
            else
                start = mid + 1;
        }
    }
    return false;
}

// ��b�е�Ԫ����a��ʹ�ö��ַ�����
void func_2(vector<int> &a, vector<int> &b) {
    for (size_t i = 0; i < b.size(); i++)
        if (!find(a, b[i]))
            cout << b[i] << " ";
    cout << endl;
}

// ��b��������Ȼ������������ŵķ�������
void func_3(vector<int> &a, vector<int> &b) {
    sort(b.begin(), b.end());
    int p1 = 0;
    int p2 = 0;
    while (p1 < a.size() && p2 < b.size()) {
        if (a[p1] < b[p2])
            p1++;
        else if (a[p1] == b[p2]) {
            //p1++;         // ��ʱ���ƶ�p1, ֻ�ƶ�p2
            p2++;
        }
        else {
            cout << b[p2++] << " ";
        }
    }
    while (p2 != b.size())
        cout << b[p2++] << " ";
    cout << endl;
}

int main() {
    vector<int> a;
    vector<int> b;
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        a.push_back(static_cast<int>(rand() % 10));
    }
    for (int i = 0; i < 5; i++) {
        b.push_back(static_cast<int>(rand() % 10));
    }
    sort(a.begin(), a.end());
    printV(a);
    printV(b);
    //cout << find(a, 10) << endl;
    func_1(a, b);
    func_2(a, b);
    func_3(a, b);

    return 0;
}