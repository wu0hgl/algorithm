#include <iostream>
#include <stdio.h>
using namespace std;

/*
    ��ӡһ���ַ�����ȫ��������, �������ַ���
*/

void printAllSub(string &str, int i, string &res) {
    if (i == str.size()) {
        //if (res.size() == 0) {
        //    return;
        //}
        printf("%s\n", res.c_str());        // ��ӡ֮ǰ���ռ��ṹ
        return;
    }
    printAllSub(str, i + 1, res);           // ��Ҫ��ǰ�ַ�
    printAllSub(str, i + 1, res + str[i]);  // Ҫ��ǰ�ַ�
}

int main() {
    string test = "abc";
    printAllSub(test, 0, string());

    return 0;
}