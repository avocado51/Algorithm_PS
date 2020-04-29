#include <iostream>
#include <vector>

using namespace std;
bool check2(string s)
{
    //연속된 3개의 문자나 숫자가 있으면 안된다.
    //3개씩 잘라서 검사
    int len = 3;
    int n = s.size();
    for (int i = 0; i < n - len; i++)
    {
        int j = len + i;
        bool flag = true;
        char c = 'A';
        for (int k = i; k < j; k++)
        {
            if (c != 'A')
            {
                if (c != s[k])
                {
                    flag = false;
                    break;
                }
            }
            c = s[k];
        }
        if (flag)
        {
            return false;
        }
    }
    return true;
}
bool check1(string s)
{
    //문자와 숫자가 있어야 한다.
    bool flag1 = 0, flag2 = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if ('0' <= s[i] && s[i] <= '9')
            flag1 = 1;
        if ('a' <= s[i] && s[i] <= 'z')
            flag2 = 1;
    }
    if (!flag1 || !flag2)
        return false;
    return true;
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string id, pass;
    cin >> id >> pass;

    if (!(6 <= id.size() && id.size() <= 12) || !(8 <= pass.size() && pass.size() <= 16))
    {
        cout << "F" << '\n';
        return 0;
    }
    if (check1(id) && check1(pass))
    {
        if (check2(pass))
            cout << "T" << '\n';
        else
            cout << "F" << '\n';
    }
    else
        cout << "F" << '\n';
    return 0;
}