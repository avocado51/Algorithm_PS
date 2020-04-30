#include <iostream>
#include <vector>

using namespace std;
//BOJ ROT13 https://www.acmicpc.net/problem/11655

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    getline(cin, s);

    for (int i = 0; i < s.size(); i++)
    {
        if ('A' <= s[i] && s[i] <= 'Z')
        {
            s[i] = (s[i] + 13) > 'Z' ? 'A' + 13 - ('Z' - s[i]) - 1 : s[i] + 13;
        }
        else if ('a' <= s[i] && s[i] <= 'z')
        {
            s[i] = (s[i] + 13) > 'z' ? 'a' + 13 - ('z' - s[i]) - 1 : s[i] + 13;
        }
    }
    cout << s << '\n';
    return 0;
}