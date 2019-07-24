#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

/*
    给定两个字符串str和match, 长度分别为N和M. 
    实现一个算法, 如果字符串str中含有子串match, 则返回match在str中的开始位置, 不含有则返回-1
*/

vector<int> getNextArray(string m) {
    vector<int> next;
    if (m.size() == 1) {
        next.push_back(-1);
        return next;
    }
    
    next.resize(m.size());
    next[0] = -1;
    next[1] = 0;
    size_t pos = 2;
    int cn = 0;
    while (pos < m.size()) {
        if (m[pos - 1] == m[cn]) {  // 当前跳到的位置和前一个字符一样, 长度确定
            next[pos++] = ++cn;
        }
        else if (cn > 0) {          // 向前跳到next数组的位置
            cn = next[cn];
        }
        else {                      // cn<0跳到最左的位置
            next[pos++] = 0;
        }
    }
    return next;
}

int getIndexOf_1(string s, string m) {
    if ((s.size() < 1) || (m.size() < 1) || (s.size() < m.size())) {
        return -1;
    }
    size_t si = 0;
    size_t mi = 0;
    vector<int> next = getNextArray(m);
    while ((si < s.size()) && (mi < m.size())) {
        if (s[si] == m[mi]) {
            si++;
            mi++;
        }
        else if (next[mi] == -1) {  // mi在m数组的开头位置, m数组开头位置的next值为-1
            si++;
        }
        else {
            mi = next[mi];
        }
    }

    /* 若匹配时, mi划过整个字符串 */
    return (mi == m.size() ? si - mi : -1); 
}

int getIndexOf_2(string& s, string& m) {
    if ((s.size() == 0) || (m.size() == 0) || (s.size() < m.size())) {
        return -1;
    }
    
    for (size_t i = 0; i < s.size(); i++) {
        size_t sPos = i;
        size_t mPos = 0;
        while ((sPos < s.size()) && (mPos < m.size())) {
            if (s[sPos] == m[mPos]) {
                sPos++;
                mPos++;
            }
            else {
                break;
            }
        }
        if (mPos == m.size()) {
            return sPos - mPos;
        }
    }
    return -1;
}

int main() {
    string str = "abcabcababaccc";
    string match = "ababa";
    //string str = "abcabc";
    //string match = "ca";

    cout << str.c_str() << endl;
    cout << match.c_str() << endl;

    cout << getIndexOf_1(str, match) << endl;
    cout << getIndexOf_2(str, match) << endl;

    return 0;
}