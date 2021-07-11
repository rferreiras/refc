#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
using namespace std;
vector<string> spitStr(const string S, string D = ",")
{
    vector<string> r;
    size_t pos = 0,
           len = S.length(),
           lenD = D.length();
    for (size_t i = 0; i < len; i++)
    {
        if (S.substr(i, lenD) == D)
        {
            r.push_back(S.substr(pos, i - pos));
            pos = i;
        }
    }
    r.push_back(S.substr(pos+1, len - pos));
    return r;
}
int main(int argc, char const *argv[])
{
    vector<string> k = spitStr("asd222:asd,sfsf,werwe:wer,lkw",",");
    vector<string> k2 = spitStr("asd222:asd",":");
    // const char regxArrStr[] = ".*(:\\[).*\\]?";
    // const char regxStringStr[] = ".*(:\").*\"?";
    // const char regxReturnStringStr[] = "(return) \".*\"";
    // const char regxReturnIntStr[] = "(return).[0-9]+";
    // const char regxReturnFloatStr[] = "(return).[0-9]+\\.[0-9]+f.*";
    // const char regxReturnDobleFloatStr[] = "(return).[0-9]+\\.[0-9]+d.*";
    // const char regxIntStr[] = ".*:\\d+[^\\.|f|d].*";
    // const char regxFloatStr[] = ".*:\\d+\\.\\df.*";
    // const char regxCallVoidFunctionStr[] = "[^:]+\\(*\\).";
    // const char regxCallReturnFunctionStr[] = "\\w.+[:]+\\w.+\\(*\\)?";

    // regex returnStringReg(regxReturnStringStr, regex::ECMAScript);
    // regex returnIntReg(regxReturnIntStr, regex::ECMAScript);
    // regex returnFloatReg(regxReturnFloatStr, regex::ECMAScript);
    // regex returnDobleFloatReg(regxReturnDobleFloatStr, regex::ECMAScript);

    // regex arrayReg(regxArrStr, regex::ECMAScript);
    // regex stringReg(regxStringStr, regex::ECMAScript);
    // regex intReg(regxIntStr, regex::ECMAScript);
    // regex floatReg(regxFloatStr, regex::ECMAScript);
    // regex callVoidFunctionReg(regxCallVoidFunctionStr, regex::ECMAScript);
    // regex callReturnFunctionReg(regxCallReturnFunctionStr, regex::ECMAScript);
    // string test = "}.}";
    // string test2 = "{";
    // string test3 = "return 5.0d";
    // string test4 = "return 55";
    // string test5 = "return 5.0fd";
    // smatch m, m2;
    // cout<<":"<<regex_match(test, m, returnDobleFloatReg)<<":"<<endl;
    // cout<<":"<<regex_match(test2, m2, returnDobleFloatReg)<<":"<<endl;
    // cout<<":"<<regex_match(test3, m2, returnDobleFloatReg)<<":"<<endl;
    // cout<<":"<<regex_match(test4, m2, returnDobleFloatReg)<<":"<<endl;
    // cout<<":"<<regex_match(test5, m2, returnDobleFloatReg)<<":"<<endl;
    return 0;
}
