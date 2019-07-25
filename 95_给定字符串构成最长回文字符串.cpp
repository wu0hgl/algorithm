#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// 使用stl中的哈希表
int longestPalindrome_1(string str) {
    unordered_map<char, int> myMap;

    for (size_t i = 0; i < str.size(); i++) {
        myMap[str[i]]++;
    }
    int res = 0;
    for (auto i : myMap) {
        res += (i.second / 2) * 2;
    }
    if (res < str.size()) {
        res++;
    }

    return res;
}

// 通过ASCII构造哈希表
int longestPalindrome_2(string str) {
    vector<int> cnts(58);
    for (size_t i = 0; i < str.size(); i++) {
        cnts[str[i] - 'A']++;
    }
    size_t res = 0;
    for (auto cnt : cnts) {
        res += (cnt / 2) * 2;
    }

    if (res < str.size()) {
        res++;
    }
    return res;
}

int main(void)
{
    string str = "abccccdd";

    cout << longestPalindrome_1(str) << endl;
    cout << longestPalindrome_2(str) << endl;

    return 0;
}