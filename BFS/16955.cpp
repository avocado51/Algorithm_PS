#include <iostream>
#include <vector>
#include <queue>

using namespace std;

char map[11][11];
bool visited[11][11];
typedef pair<int, int> pp;

// int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dx[4] = {1, 1, 1, 0}, dy[4] = {0, 1, -1, 1};

bool check()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (map[i][j] == 'X')
            {
                for (int d = 0; d < 4; d++)
                {
                    int cnt = 1;
                    int nx = i;
                    int ny = j;

                    while (nx + dx[d] >= 0 && nx + dx[d] < 10 && ny + dy[d] >= 0 && ny + dy[d] < 10 && map[nx + dx[d]][ny + dy[d]] == 'X')
                    {
                        cnt++;
                        nx += dx[d];
                        ny += dy[d];
                    }

                    if (cnt >= 5)
                        return true;
                }
            }
        }
    }
    return false;
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cin >> map[i][j];
        }
    }

    bool flag = false;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (map[i][j] == '.')
            {
                map[i][j] = 'X';

                if (check())
                {
                    flag = true;
                    break;
                }
                map[i][j] = '.';
            }
        }
        if (flag)
            break;
    }
    if (flag)
        cout << 1 << '\n';
    else
        cout << 0 << '\n';
    return 0;
}