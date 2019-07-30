#include <iostream>
#include <queue>
#include <string>
#include <functional>
#include <algorithm>
using namespace std;

int main() {
    string s;

    while (getline(cin, s)) {
        int res = 0;
        int len = s.size();
        sort(s.begin(), s.end());
        int cnt = 0;
        priority_queue<int, vector<int>, greater<int>> hp;
        for (int i = 0; i < len;) {
            int j = i;
            while (j < len && s[j] == s[i]) {
                j++;
            }
            hp.push(j - i);
            i = j;
            cnt++;
        }

        int a = 0;
        int b = 0;

        for (int i = 0; i < cnt - 1; i++) {
            a = hp.top();   hp.pop();
            b = hp.top();   hp.pop();
            hp.push(a + b);
            res += a + b;
        }
        cout << res << endl;
    }
}