#include <iostream>
#include <vector>

using namespace std;
//백준 유턴싫어 https://www.acmicpc.net/problem/2823
//unsolved

int r, c;
int map[11][11];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> r >> c;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            char tmp;
            cin >> tmp;
            if (map[i][j] == 'X')
                map[i][j] = 1;
            else
                map[i][j] = 0;
        }
    }

    //유턴은 90도로 두 번 방향을 바꾸는것.
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (!map[i][j])
            {
                //막다른길을 만나지 않고 다시 돌아올 수 있어야 한다.
            }
        }
    }

    return 0;
}
