#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
´óÊýÏà³Ë
    https://www.nowcoder.com/questionTerminal/6b668316f0ac4421ae86d7ead4301b42
*/
int main()
{
    string st1, st2;
    cin >> st1;
    cin >> st2;
    int n = st1.size();
    int m = st2.size();
    vector<int> a(n + m);
    //memset(a, sizeof(a), 0);
    //fill(a, a + n + m, 0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            a[n + m - i - j - 2] += (st1[i] - '0') * (st2[j] - '0');
    for (int i = 0; i < n + m - 1; ++i)
    {
        a[i + 1] += a[i] / 10;
        a[i] %= 10;
    }
    int r = n + m - 1;
    for (; r && !a[r]; r--);
    for (; r >= 0; --r)
        cout << a[r];
    cout << endl;
    return 0;
}