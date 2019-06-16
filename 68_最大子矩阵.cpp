#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

/*
    给定一个整型矩阵map, 其中的值只有0和1两种, 求其中全是1的所有矩形区域中, 最大的矩形区域为1的数量
    例如: {1, 1, 1, 0} = 3; {{1, 0, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 0}} = 6
*/

/* 值方图求最大长方形 */
int maxRecFromBottom(vector<int>& height) {
    if (height.size() == 0) {
        return 0;
    }

    int maxArea = 0;
    stack<int> sk;

    for (size_t i = 0; i < height.size(); i++) {
        /* 弹出结算 */
        while ((!sk.empty()) && (height[sk.top()] >= height[i])) {
            int j = sk.top();   sk.pop();
            int k = sk.empty() ? -1 : sk.top();
            int curArea = (i - k - 1) * height[j];
            maxArea = max(maxArea, curArea);
        }
        sk.push(i);
    }

    while (!sk.empty()) {
        int j = sk.top();   sk.pop();
        int k = sk.empty() ? -1 : sk.top();
        int curArea = (height.size() - k - 1) * height[j];
        maxArea = max(maxArea, curArea);
    }

    return maxArea;
}

int maxRecSize(vector<vector<int>>& map) {
    if ((map.size() == 0) || (map[0].size() == 0)) {
        return 0;
    }

    int maxArea = 0;
    vector<int> height(map[0].size(), 0);   // 辅助数组, 列数为长度
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[0].size(); j++) {
            height[j] = map[i][j] == 0 ? 0 : height[j] + 1;
        }
        maxArea = max(maxRecFromBottom(height), maxArea);
    }

    return maxArea;
}

int main() {
    vector<int> arr = { 4, 3, 2, 5, 6 };
    cout << maxRecFromBottom(arr) << endl;

    vector<vector<int>> map = { { 1, 1, 1, 0 } };
    cout << maxRecSize(map) << endl;
    
    map = { { 1, 0, 1, 1 },
            { 1, 1, 1, 1 },
            { 1, 1, 1, 0 } };
    cout << maxRecSize(map) << endl;

    return 0;
}