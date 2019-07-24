#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
using namespace std;

/*
    把一个字符串调整为大字符串, 在这个大字符串中要求包含两个原始串
    要求: 大字符串生成时只能在原始串后面添加字符串, 添加长度最短, 包含两个原始串, 开头位置不能相同, 并且大串最短
    例如: 原始串abcabc 添加abc生成大串abcabcabc, 前6个abcabc, 后6个字符abcabc共包含两个原始串
*/

int endNextLength(string &str) {
    vector<int> next;
    next.resize(str.size() + 1);
    next[0] = -1;
    next[1] = 0;
    size_t pos = 2;
    int cn = 0;
    while (pos < next.size()) {
        if (str[pos - 1] == str[cn]) {
            next[pos++] = ++cn;
        }
        else if (cn > 0) {
            cn = next[cn];
        }
        else {
            next[pos++] = 0;
        }
    }

    return next[str.size()];        // 两个返回值一样
    //return next[next.size() - 1];
}

string answer(string &str) {
    if (str.size() == 1) {
        return (str + str);
    }
    if (str.size() == 2) {
        return ((str[0] == str[1]) ? (str + str[0]) : (str + str));
    }
    int endNext = endNextLength(str);

    string res = str;
    res.append(str.begin() + endNext, str.end());
    return res;
}

int main() {
    string test1 = "a";
    printf("%s: %s\n", test1.c_str(), answer(test1).c_str());

    string test2 = "aa";
    printf("%s: %s\n", test2.c_str(), answer(test2).c_str());

    string test3 = "ab";
    printf("%s: %s\n", test3.c_str(), answer(test3).c_str());

    string test4 = "abcabc";
    printf("%s: %s\n", test4.c_str(), answer(test4).c_str());

    string test5 = "abcQabc";
    printf("%s: %s\n", test5.c_str(), answer(test5).c_str());

    string test6 = "abracadabra";
    printf("%s: %s\n", test6.c_str(), answer(test6).c_str());


    return 0;
}