#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool repeatedSubstringPattern(string s) {
    if (s.size() <= 1) {
        return false;
    }
    if (s.size() == 2) {
        return s[0] == s[1];
    }
    size_t len = s.size();
    vector<int> next;
    next.resize(len + 1);
    next[0] = -1;
    next[1] = 0;
    size_t pos = 2;
    int cn = 0;
    while (pos < len + 1) {
        if (s[pos - 1] == s[cn]) {
            next[pos++] = ++cn;
        }
        else if (cn > 0) {
            cn = next[cn];
        }
        else {
            next[pos++] = 0;
        }
    }

    //return next[len] == len;
    int lenSub = len - next[len];
    return (lenSub != len) && (len % lenSub == 0);
}

void main(void)
{
    string arr = "aaaaaa";
    //string arr{ "123123123" };
    if (repeatedSubstringPattern(arr)) {
        cout << arr.c_str() << " 是由重复字符串得到" << endl;
    }
    else {
        cout << arr.c_str() << " 不是是由重复字符串得到" << endl;
    }
}