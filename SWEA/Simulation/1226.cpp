#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;
//SWEA 미로1 [1226](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV14vXUqAGMCFAYD&)

int map[17][17];
typedef pair<int, int> pp;
bool visited[17][17];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

bool bfs(int x, int y)
{
    queue<pp> q;

    q.push({x, y});
    visited[x][y] = true;

    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= 16 || ny < 0 || ny >= 16 || visited[nx][ny])
                continue;

            if (map[nx][ny] == 3)
                return true;

            if (map[nx][ny] != 1)
            {
                visited[nx][ny] = true;
                q.push(pp(nx, ny));
            }
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 10;
    for (int tc = 1; tc <= t; tc++)
    {
        memset(visited, 0, sizeof(visited));

        char c;
        int x, y;
        int n;
        cin >> n;
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                cin >> c;
                map[i][j] = c - '0';
                if (map[i][j] == 2)
                {
                    x = i;
                    y = j;
                }
            }
        }

        cout << "#" << n << " " << bfs(x, y) << '\n';
    }
    return 0;
}