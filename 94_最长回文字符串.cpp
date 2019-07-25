#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

string longestPalindrome(string str) {
    if (str.size() == 0) {
        return string();
    }

    string charArr = "$#";
    for (int i = 0; i < str.size(); ++i) {
        charArr += str[i];
        charArr += "#";
    }

    vector<int> pArr(charArr.size());
    int pR = -1;
    int index = -1;
    
    int resCenter = -1;
    int reslen = -1;

    for (int i = 0; i < charArr.size(); i++) {
        pArr[i] = pR > i ? min(pArr[2 * index - i], pR - i) : 1;
        while (i + pArr[i] < charArr.size() && i - pArr[i] > -1) {
            if (charArr[i + pArr[i]] == charArr[i - pArr[i]])
                pArr[i]++;
            else {
                break;
            }
        }
        if (i + pArr[i] > pR) {
            pR = i + pArr[i];
            index = i;
        }

        if (reslen < pArr[i]) {
            reslen = pArr[i];
            resCenter = i;
        }

        if (pR == charArr.size()) {
            break;
        }
    }

    return str.substr((resCenter - reslen) / 2, reslen - 1);
}

int main() {
    string s1 = "12212";
    cout << s1.c_str() << endl;
    cout << longestPalindrome(s1).c_str() << endl;
    cout << "=======================" << endl;

    string s2 = "122122";
    cout << s2.c_str() << endl;
    cout << longestPalindrome(s2).c_str() << endl;
    cout << "=======================" << endl;

    string s3 = "waabwswfd";
    cout << s3.c_str() << endl;
    cout << longestPalindrome(s3).c_str() << endl;
    cout << "=======================" << endl;

    return 0;
}