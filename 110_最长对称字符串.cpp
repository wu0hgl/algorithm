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


int res = 0;;
void func(string& str, int L, int R, int len) {
    if (L > R)
        return;
    if (L == R) {
        if (str[L] == str[R]) {
            len += 1;
            res = len > res ? len : res;
        }
        return;
    }
    if (str[L] == str[R]) {
        len += 2;
        res = len > res ? len : res;
        func(str, L + 1, R - 1, len);
    }
    else {
        func(str, L + 1, R, len);
        func(str, L, R - 1, len);
    }
}

int main() {
    string str = "abcba";
    func(str, 0, str.size() - 1, 0);
    cout << res << endl;

    res = 0;
    str = "abcdeba";
    func(str, 0, str.size() - 1, 0);
    cout << res << endl;

    res = 0;
    str = "aeaabab";
    func(str, 0, str.size() - 1, 0);
    cout << res << endl;
}