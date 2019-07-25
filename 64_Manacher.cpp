#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxLcpsLength(string &str) {
    if (str.size() == 0) {
        return 0;
    }

    string charArr = "#";
    for (int i = 0; i < str.size(); ++i) {
        charArr += str[i];
        charArr += "#";
    }

    vector<int> pArr(charArr.size());   // 回文半径数组
    int pR = -1;                        // 回文半径即将到达的位置
    int index = -1;                     // 取得最右边界时的回文中心

    int myMax = INT_MIN;

    for (int i = 0; i != charArr.size(); i++) { // 每个回文的中心
        // (1) i不在回文在回文右边界, 暴力扩
        // (2) i在回文半径内, i的对称点i'的回文半径在当前回文左边界内, pArr[i] = pArr[2 * index - i]
        // (3) i在回文半径内, i的对称点i'的回文半径在当前回文左边界外, pArr[i] = pR - i
        // (4) i在回文半径内, i的对称点i'的回文半径当前回文左边界重合, 两边不确定, 暴力扩

        /*  
            pR > i表示i在回文右边界里面
            2 * index - i 对称点i'位置 
        */
        pArr[i] = pR > i ? min(pArr[2 * index - i], pR - i) : 1;    // 情况2与情况3

        /* i+pArr[i] < charArr.size()验证右区域没越界, i - pArr[i] > -1验证左边区域也没越界 */
        while (i + pArr[i] < charArr.size() && i - pArr[i] > -1) {
            if (charArr[i + pArr[i]] == charArr[i - pArr[i]])       // 情况1与情况4都会向外暴力扩, 判断下一位两边字符是否相同
                pArr[i]++;                                          // 情况1只会扩一个, 情况4可能会扩多个
            else {                                                  // 情况2与情况3不会外扩
                break;                                          
            }
        }
        if (i + pArr[i] > pR) {
            pR = i + pArr[i];
            index = i;
        }

        myMax = max(myMax, pArr[i]);

        /* 下面注释可以去掉 */
        //if (pR == charArr.size()) {
        //    break;
        //}
    }
    return myMax - 1;
}


int main() {
    string s1 = "12212";
    cout << s1.c_str() << endl;
    cout << maxLcpsLength(s1) << endl;
    cout << "=======================" << endl;
    
    string s2 = "122122";
    cout << s2.c_str() << endl;
    cout << maxLcpsLength(s2) << endl;
    cout << "=======================" << endl;

    string s3 = "waabwswfd";
    cout << s3.c_str() << endl;
    cout << maxLcpsLength(s3) << endl;
    cout << "=======================" << endl;

    string s4 = "waabwswfdswbaaw";
    cout << s4.c_str() << endl;
    cout << maxLcpsLength(s4) << endl;

    return 0;
}