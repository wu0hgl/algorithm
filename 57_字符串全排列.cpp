#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include <algorithm>
#include <stdio.h>
using namespace std;
void printArr(vector<string> &arr);

/*
    输入一个字符串(输入一个字符串,长度不超过9, 可能有字符重复, 字符只包括大小写字母), 按字典序打印出该字符串中字符的所有排列. 
    例如输入字符串abc, 则打印出由字符a, b, c所能排列出来的所有字符串abc, acb, bac, bca, cab和cba.
*/

void process_1(string &str, int begin, vector<string> &res) {
    if (begin == str.size()) {
        res.push_back(str);
        return;
    }
    for (size_t i = begin; i < str.size(); i++) {
        /* 排除重复字符串 */
        if ((i != begin) && (str[begin] == (str[i]))) {
            continue;
        }
        swap(str[begin], str[i]);    // 交换
        process_1(str, begin + 1, res);
        swap(str[begin], str[i]);    // 恢复
    }
}
vector<string> printAllPermutations1(string str) {
    vector<string> res;

    if (str.size() == 0) {
        return res;
    }
    process_1(str, 0, res);
    sort(res.begin(), res.end());    // 使用库函数排序
    return res;
}

/* 使用set去重 */
struct strComp
{
    bool operator() (const string& str1, const string& str2) const {
        return str1 < str2;
    }
};
void process_2(string &str, int begin, set<string, strComp> &mySet) {
    if (begin == str.size()) {
        mySet.insert(str);
    }
    for (int i = begin; i < str.size(); i++) {
        swap(str[begin], str[i]);
        process_2(str, begin + 1, mySet);
        swap(str[begin], str[i]);
    }
}
vector<string> printAllPermutations2(string str) {
    vector<string> res;
    set<string, strComp> mySet;
    if (str.size() == 0) {
        return res;
    }
    process_2(str, 0, mySet);
    for (set<string>::iterator it = mySet.begin(); it != mySet.end(); it++) {
        res.push_back(*it);
    }
    return res;
}

int main() {
    string str_1("aacd");
    vector<string> res;

    res = printAllPermutations1(str_1);
    printArr(res);

    res = printAllPermutations2(str_1);
    printArr(res);

    return 0;
}

void printArr(vector<string> &arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        printf("%s\t", arr[i].c_str());
    }
    cout << endl;
}