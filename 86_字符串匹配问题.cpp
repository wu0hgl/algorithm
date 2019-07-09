#include <iostream>
#include <string>
using namespace std;

/*
    给定字符串str, 其中绝对不含有字符`.`和`*`. 再给定字符串exp, 其中可以含有`.`或`*`, `*`字符不能是exp的首字符, 并且任意两个`*`字符不相邻. 
    exp中的`.`代表任何一个字符, exp中的`*`表示`*`的前一个字符可以有0个或者多个. 
    请写一个函数, 判断str是否能被exp匹配
        例如:
        `str="abc"; exp="abc"`, 返回true
        `str="abc"; exp="a.c"`, exp中单个'.'可以代表任意字符, 所以返回true
        `str="abcd"; exp=".*"`, exp中`*`的前一个字符是`.`, 所以可表示任意数量的`.`字符, 当exp是`....`时与`abcd`匹配, 返回true
        `str=""， exp="..*"`, exp中`*`的前一个字符是`.`, 可表示任意数量的`.`字符, 但是`.*`之前还有一个`.`字符, 该字符不受`*`的影响, 所以str起码有一个字符才能被exp匹配. 所以返回false
*/

bool isValid(string& str, string& exp) {
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == '*' || str[i] == '.') {
            return false;
        }
    }
    for (size_t i = 0; i < exp.size(); i++) {
        if (exp[i] == '*' && (i == 0 || exp[i - 1] == '*')) {
            return false;
        }
    }
    return true;
}

bool process(string& str, int si, string& exp, int ei) {
    /* exp已经匹配到末尾 */
    if (ei == exp.size()) {
        return si == str.size();    // str是否匹配到末尾
    }

    /* 最后一个字符, 或者exp的下一个字符不是*的情况 */
    if (/* exp到最后一个字符 */(ei + 1 == exp.size()) || /* exp的下一个字符不是* */(exp[ei + 1] != '*')) {
        return si != str.size()                             // 当前str字符没有匹配完
               && (exp[ei] == str[si] || exp[ei] == '.')    // 当前str字符与exp字符匹配, 或者当前exp字符是., 则继续匹配后续字符
               && process(str, si + 1, exp, ei + 1);        // 继续考察下一位
    }

    /* exp的下一个字符是*的情况 */
    while ((si != str.size()) && (exp[ei] == str[si] || exp[ei] == '.')) {
        if (process(str, si, exp, ei + 2)) {    // aaab与a*xx的情况, 匹配0个a的情况
            return true;
        }
        si++;
    }

    // aaab与b*xx的情况, 没有进入上面的while, exp直接向后跳两个字符继续匹配
    return process(str, si, exp, ei + 2);
}

bool isMatch(string& str, string& exp) {
    if ((str.size() == 0) || (exp.size() == 0)) {
        return false;
    }
    return isValid(str, exp) && process(str, 0, exp, 0);
}

int main() {
    //string str = "abcccdefg";
    ////string exp = "ab.*d.*e.*";
    //string exp = ".*";
    string str = "aaab";
    string exp = "a*xx";

    cout << isMatch(str, exp) << endl;

    return 0;
}