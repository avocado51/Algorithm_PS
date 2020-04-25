#include <iostream>
#include <vector>

using namespace std;

//boj https://www.acmicpc.net/problem/4378

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string keyBoard[4] = {"`1234567890-=", "QWERTYUIOP[]\\", "ASDFGHJKL;\'", "ZXCVBNM,./"};

    string input;
    while (getline(cin, input))
    {
        string output = "";

        for (char c : input)
        {
            bool chk = 0;
            if (c == ' ')
                cout << c;
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < keyBoard[i].size(); j++)
                    {
                        if (keyBoard[i][j] == c)
                        {
                            cout << keyBoard[i][j - 1];
                            chk = 1;
                            break;
                        }
                    }
                    if (chk)
                        break;
                }
            }
        }
        cout << '\n';
    }
    return 0;
}