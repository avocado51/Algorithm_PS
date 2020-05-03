#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
//백준 유턴싫어 https://www.acmicpc.net/problem/2823

int r, c;
char map[11][11];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

bool checkRange(int x, int y)
{
    if (x < 0 || x >= r || y < 0 || y >= c || map[x][y] == 'X')
        return false;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> r >> c;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> map[i][j];
        }
    }

    //유턴은 90도로 두 번 방향을 바꾸는것.-> 연속해서 방향을 바꾸면 그것도 유턴으로 간주한다.

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (map[i][j] == '.')
            {
                //임의의 한 점에서 시작
                int cnt = 0;
                for (int k = 0; k < 4; k++)
                {
                    if (!visited[k][i][j])
                    {
                        int nx = i + dx[k];
                        int ny = j + dy[k];

                        if (checkRange(nx, ny))
                        {
                            cnt++;
                        }
                    }
                }
                if (cnt <= 1)
                {
                    //갈 수 있는 곳이 하나밖에 없거나, 아예 없다면 유턴밖에 답이 없다.
                    cout << 1 << '\n';
                    exit(0);
                }
            }
        }
    }
    cout << 0 << '\n';
    return 0;
}
