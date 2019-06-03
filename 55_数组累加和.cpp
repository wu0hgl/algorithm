#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

/*
    数组累加和
*/

bool isSum(vector<int> &arr, int i, int sum, int aim) {
    if (i == arr.size()) {
        return sum == aim;      // base case
    }
    return isSum(arr, i + 1, sum, aim) || isSum(arr, i + 1, sum + arr[i], aim);
}

int main() {
    vector<int> arr = { 1, 4, 8 };
    cout << isSum(arr, 0, 0, 12) << endl;

    return 0;
}