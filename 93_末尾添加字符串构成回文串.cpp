#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

/*
    只能够向字符串最后添加字符, 怎么能够让字符串整体都变成回文串. 
    要求添加字符最少
*/

string shortEnd(string& str) {
    string res;
    if (str.size() == 0) {
        return res;
    }

    string charArr = "#";
    for (int i = 0; i < str.size(); ++i) {
        charArr += str[i];
        charArr += "#";
    }
    vector<int> pArr = vector<int>(charArr.size());
    int index = -1;
    int pR = -1;

    int maxContainsEnd = -1;
    int myMax = 0;

    for (int i = 0; i < charArr.size(); i++) {
        pArr[i] = pR > i ? min(pArr[2 * index - i], pR - i) : 1;

        while ((i + pArr[i] < charArr.size()) && (i - pArr[i] > -1)) {
            if (charArr[i + pArr[i]] == charArr[i - pArr[i]]) {
                pArr[i]++;
            }
            else {
                break;
            }
        }
        if (i + pArr[i] > pR) {
            pR = i + pArr[i];
            index = i;
        }

        myMax = max(myMax, pArr[i]);
        if (pR == charArr.size()) {
            maxContainsEnd = pArr[i];
            break;
        }
    }

    //res.resize(str.size() - myMax + 1);           // myMax是求最大回文字符串的长度
    res.resize(str.size() - maxContainsEnd + 1);    // maxContainsEnd是第一次扩到最右边是的回文中心对应的回文半径
    for (size_t i = 0; i < res.size(); i++) {
        res[res.size() - 1 - i] = charArr[i * 2 + 1];
    }

    return res;
}

int main() {
    string str = "abcd123321";
    cout << str.c_str() << endl;
    cout << shortEnd(str).c_str() << endl;
    cout << "=======================" << endl;

    string s1 = "12212";
    cout << s1.c_str() << endl;
    cout << shortEnd(s1).c_str() << endl;
    cout << "=======================" << endl;

    string s2 = "122122";
    cout << s2.c_str() << endl;
    cout << shortEnd(s2).c_str() << endl;
    cout << "=======================" << endl;

    string s3 = "waabwswfd";
    cout << s3.c_str() << endl;
    cout << shortEnd(s3).c_str() << endl;
    cout << "=======================" << endl;
}