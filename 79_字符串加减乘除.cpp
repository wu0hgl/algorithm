#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

/*
    给定一个字符串str, str表示一个公式, 公式里可能有整数, 加减乘除符号和左右括号, 返回公式的计算结果. 说明:
        (1)可以认为给定的字符串一定是正确的公式， 即不需要对str做公式有效性检查。
        (2)如果是负数, 就需要用括号括起来, 比如`4*(-3)`. 但如果负数作为公式的开头或括号部分的开头, 则可以没有括号, 比如`-3*4`和`(-3*4)`都是合法的。
        (3)不用考虑计算过程中会发生溢出的情况
*/

void addNum(list<string>& que, int num) {
    if (!que.empty()) {
        int cur = 0;
        string top = que.back(); que.pop_back();
        if ((top == "+") || (top == "-")) {         // +, -不操作
            que.push_back(top);                     // 把弹出的字符串再压入list中
        }
        else {                                      // *, / 计算
            cur = stoi(que.back(), nullptr, 10);    // 再取出一个数字进行计算
            que.pop_back();
            num = top == "*" ? (cur * num) : (cur / num);
        }
    }
    que.push_back(to_string(num));
}

int getNum(list<string>& que) {     // 结算收集到的数字
    int res = 0;
    bool add = true;
    string cur;
    int num = 0;
    while (!que.empty()) {
        cur = que.front();  que.pop_front();
        if (cur == "+") {
            add = true;
        }
        else if (cur == "-") {
            add = false;
        }
        else {
            num = stoi(cur, nullptr, 10);
            res += add ? num : (-num);
        }
    }
    return res;
}

vector<int> value(string str, size_t i) {
    list<string> que;
    int pre = 0;
    vector<int> bra;
    while ((i < str.size()) && (str[i] != ')')) {
        if ((str[i] >= '0') && (str[i] <= '9')) {     // 收集数字
            pre = pre * 10 + (str[i++] - '0');
        }
        else if (str[i] != '(') {                   // 遇到运算符号进行计算(+ , -, *, /)
            addNum(que, pre);

            string temp;
            temp += str[i++];
            que.push_back(temp);

            pre = 0;    // 计算之后把收集的数字置0
        }
        else {
            bra = value(str, i + 1);                // 遇到左括号
            pre = bra[0];
            i = bra[1] + 1;
        }
    }
    addNum(que, pre);

    vector<int> ret;
    ret.push_back(getNum(que));
    ret.push_back(i);

    return ret;
}

int getValue(string& str) {
    return value(str, 0)[0];
}

int main() {
    string exp = " 48 *((70-65)-43)+8*1";
    //string exp = "12*((11-12)-21)+1*2";
    cout << getValue(exp) << endl;


    return 0;
}