#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ctime>
using namespace std;
void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue);
void printVector(vector<int> &vt);
void printVt(vector<vector<int>> &vt);
int f(vector<int> arr, int i, int j);
int s(vector<int> arr, int i, int j);

/*
    给定一个整型数组arr, 代表数值不同的纸牌排成一条线. 
    玩家A和玩家B依次拿走每张纸牌, 规定玩家A先拿, 玩家B后拿, 但是每个玩家每次只能拿走最左或最右的纸牌, 玩家A和玩家B都绝顶聪明. 
    返回最后获胜者的分数
*/

int f(vector<int> arr, int i, int j) {  // 先拿
    if (i == j) {       // i==j时, 先拿的人只有一种选择arr[i]
        return arr[i];
    }
    /* 当前玩家拿牌后变成后拿玩家 */
    return max(arr[i] + s(arr, i + 1, j), arr[j] + s(arr, i, j - 1));   
}
int s(vector<int> arr, int i, int j) {  // 后拿
    if (i == j) {       // i==j时, 后拿的人只有一种选择0
        return 0;
    }
    /* 当前玩家拿牌后变成先拿玩家,  */
    return min(f(arr, i + 1, j), f(arr, i, j - 1)); // 对手先拿, 会把最差情况留给当前玩家, 所以是min
}

int win_1(vector<int>& arr) {
    if (arr.size() == 0) {
        return 0;
    }
    return max(f(arr, 0, arr.size() - 1), s(arr, 0, arr.size() - 1));
}

/*
    递归中i不可能大于j, 所以表f与表s的左下半部分全为0
    f表的对角线位置根据递归i==j情况, 等于arr[i]
    s表的对角线位置根据递归i==j情况, 等于0
*/
int win_2(vector<int>& arr) {
    if (arr.size() == 0) {
        return 0;
    }
    vector<vector<int>> f(arr.size(), vector<int>(arr.size()));
    vector<vector<int>> s(arr.size(), vector<int>(arr.size()));

    for (size_t j = 0; j < arr.size(); j++) {
        f[j][j] = arr[j];
        for (int i = j - 1; i >= 0; i--) {
            f[i][j] = max(arr[i] + s[i + 1][j], arr[j] + s[i][j - 1]);
            s[i][j] = min(f[i + 1][j], f[i][j - 1]);
        }
    }

    return max(f[0][arr.size() - 1], s[0][arr.size() - 1]);
}

int main() {
    //vector<int> arr = { 1, 2, 100, 4 };
    vector<int> arr;
    generatorRandomArray(arr, 5, 5);
    printVector(arr);

    cout << win_1(arr) << endl;
    cout << win_2(arr) << endl;

    return 0;
}

void printVector(vector<int> &vt) {
    for (auto v : vt)
        cout << v << " ";
    cout << endl;
}

void printVt(vector<vector<int>> &vt) {
    for (size_t i = 0; i < vt.size(); i++) {
        for (size_t j = 0; j < vt[0].size(); j++) {
            cout << vt[i][j] << " ";
        }
        cout << endl;
    }
}

void generatorRandomArray(vector<int> &vt, int maxSize, int maxValue) {
    int temp;
    int len = (int)(maxSize % (maxSize + 1));

    srand(static_cast<int>(time(NULL)));
    for (int i = 0; i < len; i++) {
        //temp = static_cast<int>(rand() % (maxValue + 1)) - static_cast<int>(rand() % (maxValue));   // 随机生成正负数
        temp = static_cast<int>(rand() % (maxValue + 1));          // 随机生成正数
        if (temp == 0) {
            continue;
        }
        else {
            vt.push_back(temp);
        }
    }
}