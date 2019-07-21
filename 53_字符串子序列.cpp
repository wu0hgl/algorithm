#include <iostream>
#include <stdio.h>
using namespace std;

/*
    打印一个字符串的全部子序列, 包括空字符串
*/

void printAllSub(string &str, int i, string &res) {
    if (i == str.size()) {
        //if (res.size() == 0) {
        //    return;
        //}
        printf("%s\n", res.c_str());        // 打印之前的收集结构
        return;
    }
    printAllSub(str, i + 1, res);           // 不要当前字符
    printAllSub(str, i + 1, res + str[i]);  // 要当前字符
}

int main() {
    string test = "abc";
    printAllSub(test, 0, string());

    return 0;
}