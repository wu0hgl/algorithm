#include <iostream>
using namespace std;

/*
给定的字符串里面, 找出最长的对称字符串(可以跳过部分字符)
输入: 字符串
输出: 最长字符串的长度
abcba   --> 5
abcdeba --> 5 (abcba与abcba)
aeaabab --> 4 (aaaa与aaaa对称)
*/

int max = 0;

void func(string& s, int begin, int end, int len){
    if (begin > end) return;
    if (begin == end){
        len += 1;
        if (len > max){
            max = len;
        }
        return;
    }
    if (str[begin] == str[end]){
        if (len + 2 > max){
            max = len + 2;
        }
        func(str, begin + 1, end - 1, len + 2);
    }
    func(str, begin + 1, end, len);
    func(str, begin, end - 1, len);
}

int main() {
    string str = "abcba";
    func(str, 0, str.size() - 1, 0);
    cout << max << endl;

    max = 0;
    str = "abcdeba";
    func(str, 0, str.size() - 1, 0);
    cout << max << endl;

    max = 0;
    str = "aeaabab";
    func(str, 0, str.size() - 1, 0);
    cout << max << endl;
}