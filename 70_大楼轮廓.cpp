#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
void printVector(vector<vector<int>>& arr);

/*
    给定一个N行3列二维数组, 每一行表示有一座大楼, 一共有N座大楼. 
    所有大楼的底部都坐落在X轴上, 每一行的三个值(a,b,c)代表每座大楼的从(a,0)点开始, 到(b,0)点结束, 高度为c.
    输入的数据可以保证a<b,且a, b, c均为正数. 大楼之间可以有重合. 请输出整体的轮廓线
    例子: 给定一个二维数组{{1, 3, 3}, {2, 4, 4}, {5, 6, 1}}, 输出轮廓线{{1, 2, 3}, {2, 4, 4}, {5, 6, 1}}
*/

class Node {
public:
    Node(bool bORe, int position, int height) {
        isUp = bORe;
        posi = position;
        h = height;
    }

    bool isUp;
    int posi;
    int h;
};

bool comparator(const Node& a, const Node& b) { 
    if (a.posi != b.posi) {             // 位置不同时, 先出现的位置在前面
        return (a.posi < b.posi);
    }
    if (a.isUp != b.isUp) {             // 位置相同时, 上位置在前
        return a.isUp ? true : false;
    }
    return 0;                           // 随意
    //return (a.posi < b.posi); 
}

vector<vector<int>> buildingOutline(vector<vector<int>> &buildings) {
    vector<Node> nodes;
    for (size_t i = 0; i < buildings.size(); i++) {
        nodes.push_back(Node(true, buildings[i][0], buildings[i][2]));
        nodes.push_back(Node(false, buildings[i][1], buildings[i][2]));
    }

    sort(nodes.begin(), nodes.end(), comparator);   // 按位置排序

    map<int, int> htMap;        // key: 高度; value: 高度出现的次数, 利用map的从小到大排序查找当前最大高度
    map<int, int> pmMap;        // key: 位置; value: 高度

    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i].isUp) {    // 上 -> htMap添加
            if (!htMap.count(nodes[i].h)) {     // 第一次出现, 计数值=1
                htMap[nodes[i].h] = 1;
            }
            else {                              // 非第一次出现, 计数值-1
                htMap[nodes[i].h] = htMap[nodes[i].h] + 1;
            }
        }
        else {                  // 下  -> htMap移除
            if (htMap.count(nodes[i].h)) {
                if (htMap[nodes[i].h] == 1) {   // 第一次出现, 移除节点
                    htMap.erase(nodes[i].h);
                }
                else {                          // 非第一次出现, 计数值-1
                    htMap[nodes[i].h] = htMap[nodes[i].h] - 1;
                }
            }
        }

        /* 收集每个位置的最大高度 */
        if (htMap.empty()) {
            pmMap[nodes[i].posi] = 0;
        }
        else {
            /* int类型map自动从小到大排序, 最后一个值为当前红黑树最大值 */
            pmMap[nodes[i].posi] = htMap.rbegin()->first;   
        }
    }

    vector<vector<int>> ret;
    int start = 0;
    int height = 0;     // 记录之前的高度
    for (map<int, int>::iterator it = pmMap.begin(); it != pmMap.end(); it++) { // 利用pmMap升序来取位置
        int curPosition = it->first;
        int curMaxHeight = it->second;
        if (height != curMaxHeight) {   // 之前高度 != 当前最大高度
            if (height != 0) {          // 之前高度 != 0, 生成轮廓线
                vector<int> newRecord;
                newRecord.push_back(start);
                newRecord.push_back(curPosition);
                newRecord.push_back(height);
                ret.push_back(newRecord);
            }
            start = curPosition;
            height = curMaxHeight;
        }
    }

    return ret;
}

int main() {
    vector<vector<int>> arr;
    vector <vector<int>> res;

    arr = { { 1, 3, 3 }, 
            { 2, 4, 4 }, 
            { 5, 6, 1 } };
    res = buildingOutline(arr);
    printVector(res);
    cout << "====================" << endl;
    arr = { { 2, 5, 6 }, 
            { 1, 7, 4 }, 
            { 4, 6, 7 },
            { 3, 6, 5 },
            { 10, 13, 2 },
            { 9, 11, 3 },
            { 12, 14, 4 },
            { 10, 12, 5 } };
    res = buildingOutline(arr);
    printVector(res);

    return 0;
}

void printVector(vector<vector<int>>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        for (size_t j = 0; j < arr[0].size(); j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}