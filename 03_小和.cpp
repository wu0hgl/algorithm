#include <iostream>
#include <ctime>
using namespace std;

/*
    ��һ��������, ÿһ������߱ȵ�ǰ��С�����ۼ�����, ������������С��. ��һ�����ֵ�С��. ��[1, 3, 4, 2, 5]С��Ϊ16
*/

void printArr(int *a, int len) {
    for (auto i = 0; i < len; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int merge(int *arr, int left, int mid, int right) {
    int lowPtr = left;      // ����α�
    int hightPtr = mid + 1; // �Ҳ��α�

    int *temp = (int *)malloc((right - left + 1) * sizeof(int));
    int ptr = 0;
    int res = 0;

    while (lowPtr <= mid && hightPtr <= right) {
        res += (arr[lowPtr] < arr[hightPtr] ? arr[lowPtr] * (right - hightPtr + 1) : 0);    // û���˷�С��Χ�Ƚ�ʱ�Ĵ���
        temp[ptr++] = arr[lowPtr] < arr[hightPtr] ? arr[lowPtr++] : arr[hightPtr++];
    }
    while (lowPtr <= mid) {
        temp[ptr++] = arr[lowPtr++];
    }
    while (hightPtr <= right)
        temp[ptr++] = arr[hightPtr++];

    for (ptr = 0; ptr < (right - left + 1); ptr++) {
        arr[left + ptr] = temp[ptr];
    }
    free(temp);

    return res;
}

int mergeSort(int *arr, int left, int right) {
    if (left == right)
        return 0;

    int mid = left + ((right - left) >> 2);

    return (mergeSort(arr, left, mid)
        + mergeSort(arr, mid + 1, right)
        + merge(arr, left, mid, right));
}

int main() {
    int arr[5];
    int len = sizeof(arr) / sizeof(int);
    srand(time(NULL));
    for (int i = 0; i < len; i++) {
        arr[i] = static_cast<int>(rand() % 5);
    }
    printArr(arr, len);

    cout << mergeSort(arr, 0, len - 1) << endl;
    printArr(arr, len);

    return 0;
}