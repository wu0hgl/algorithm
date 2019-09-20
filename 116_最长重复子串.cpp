#include <iostream>
#include <string>
#include <vector>
using namespace std;

int func(string& str, string& out) {
    vector<int> next(str.size() + 1);
    if (str.size() == 0 || str.size() == 1) {
        return 0;
    }
    next[0] = -1;
    next[1] = 0;
    int res = 0;
    int pos = 2;
    int cnt = 0;
    while (pos < next.size()) {
        if (str[pos - 1] == str[cnt]) {
            next[pos++] = ++cnt;
        }
        else if (cnt > 0) {
            cnt = next[cnt];
        }
        else {
            next[pos++] = 0;
        }
        if (next[pos - 1] > res) {
            res = next[pos - 1];
            out = str.substr(0, res);
        }
    }
    return res;
}

string longestDupSubstring(string str) {
    int size = 0;
    string res;
    for (int i = 0; i < str.size(); i++) {
        string temp_str = str.substr(i);
        string out;
        int temp_len = func(temp_str, out);
        if (temp_len > size) {
            res = out;
            size = temp_len;
        }
    }
    return res;
}


int main() {
    string str = "abcd";
    string res = longestDupSubstring(str);
    cout << res << endl;
    cout << "=============" << endl;
    
    str = "banana";
    res = longestDupSubstring(str);
    cout << res << endl;

    return 0;
}